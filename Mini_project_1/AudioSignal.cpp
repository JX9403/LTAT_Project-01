#include <ios>
#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>
#include <numeric>
#include <stdio.h>
#include "AudioSignal.h"
#include "gnuplot-iostream.h"
#include "wav.h"
#include <cmath>

using namespace std;
using ll = long long;
double const pi = 3.14159265358979323846;
// Hàm khởi tạo
AudioSignal::AudioSignal(std::vector<std::pair<double, double>> values, double rate)
{
    this->values = values;
    this->rate = rate;
}
//----------------------vẽ biểu đồ tín hiệu -----------------------------------------------------------------------------

void AudioSignal::drawPlot() const {
    // tạo đối tượng gnuplot
    Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"");

    //set tên trục x, trục y cho biểu đồ
    gp << "set xlabel 'n'\nset ylabel 'x(n)'\n";

    gp << "plot '-' with lines title 'Line'" << std::endl;

    vector <double> v;
    for (long long i = 0; i < values.size(); i++)
    {
        v.push_back(values[i].second);
    }

    gp.send(v);

    std::cout << "Press enter to out!";
    // đợi lệnh tiếp theo từ người dùng
    std::cin.get();
}

//*************************CÁC PHÉP TOÁN TRÊN TÍN HIỆU***************************************

//---------------------------------TimeShift-------------------------------------------------

void AudioSignal::timeShift(long long m) {

    vector <pair<double, double>> shiftedValues(values.size() + abs(m));
    // m < 0 , x[n]  dich trai m don vi 

    if (m < 0) {
        for (ll i = 0; i < shiftedValues.size(); i++) {
            if (i < values.size()) {
                shiftedValues[i].first = values[i].first + m;
                shiftedValues[i].second = values[i].second;
            }
            else {
                shiftedValues[i].first = shiftedValues[i - 1].first + 1;
                shiftedValues[i].second = 0;
            }
        }
    }
    // m > 0 , x[n]  dich phai m don vi 
    else if (m > 0) {

        for (ll i = shiftedValues.size() - 1; i >= 0; i--) {
            if (i >= m) {
                shiftedValues[i].first = values[i - m].first + m;
                shiftedValues[i].second = values[i - m].second;
            }
            else {
                shiftedValues[i].first = shiftedValues[i + 1].first - 1;
                shiftedValues[i].second = 0;
            }
        }



    }
    values = shiftedValues;
    std::cout << "Time Shifting success!\n";
}

vector<pair<double, double>> AudioSignal::timeShiftVector(vector<pair<double, double>> values, long long m) {

    vector <pair<double, double>> shiftedValues(values.size() + abs(m));
    // m < 0 , x[n]  dich trai m don vi 

    if (m < 0) {
        for (ll i = 0; i < shiftedValues.size(); i++) {
            if (i < values.size()) {
                shiftedValues[i].first = values[i].first + m;
                shiftedValues[i].second = values[i].second;
            }
            else {
                shiftedValues[i].first = shiftedValues[i - 1].first + 1;
                shiftedValues[i].second = 0;
            }
        }
    }
    // m > 0 , x[n]  dich phai m don vi 
    else if (m > 0) {

        for (ll i = shiftedValues.size() - 1; i >= 0; i--) {
            if (i >= m) {
                shiftedValues[i].first = values[i - m].first + m;
                shiftedValues[i].second = values[i - m].second;
            }
            else {
                shiftedValues[i].first = shiftedValues[i + 1].first - 1;
                shiftedValues[i].second = 0;
            }
        }



    }
     return shiftedValues;

}

//---------------------------------Phep dao thoi gian----------------------------------------

void AudioSignal::reverseTime() {
    vector<pair<double, double>> reverseValues = values;
    // đảo ngược vector
    reverse(reverseValues.begin(), reverseValues.end());

    // trả lại chỉ số tín hiệu sau khi đã đảo 
    for (ll i = 0; i < values.size(); i++) {
        //reverseValues[i].first = values[i].first;
        reverseValues[i].first = -reverseValues[i].first;
    }
    values = reverseValues;

    cout << "Reverse Time success!\n";
}

//---------------------------------Giảm tần số lấy mẫu--------------------------------------

    // Cứ mỗi m mẫu thì lấy mẫu đầu tiên, loại bỏ các mẫu sau
    // hiệu ứng chậm hơn
void AudioSignal::downsample(int m) {

    // giảm tần số lấy mẫu
    rate /= m;

    vector <pair<double, double>> downSampleValues;

    ll j = 0;

    for (ll i = 0; i < values.size(); i += m) {
        pair<double, double > tmp;
        tmp.second = values[i].second; // giu lai gia tri cua mau
        tmp.first = j; // dat chi so moi
        j++;

        downSampleValues.push_back(tmp);
    }

    values = downSampleValues;

    cout << "Downsample success!\n";
}
//------------------------------------------------------------------------------------------
    // Tăng tấn số lấy mẫu 

void AudioSignal::upsample(int l) {

    //tăng tần số lấy mẫu
    rate *= l;

    vector <pair<double, double>> upSampleValues;

    // giữ vị trí chỉ số mới
    ll j = values[0].first;

    for (long long i = 0; i < values.size(); ++i) {
        // giữ lại mẫu đầu tiên
        if (i != 0) {
            j++; // Tăng chỉ số mẫu
        }

        // Tạo mẫu mới với giá trị giống mẫu đã có
        pair<double, double> tmp;
        tmp.second = values[i].second;
        tmp.first = j;

        // Thêm mẫu mới vào vector 
        upSampleValues.push_back(tmp);

        // Nếu không phải mẫu cuối cùng trong values
        if (i == values.size() - 1) {
            break;
        }

        // Thêm các mẫu ở giữa mỗi cặp mẫu liền kề
        for (ll i2 = 1; i2 < l; i2++) {
            j++;
            upSampleValues.push_back({ j, 0 }); // Giá trị của mẫu mới là 0
        }
    }

    // Gán lại vector mẫu đã tăng tần số cho values
    values = upSampleValues;

    // In ra thông báo thành công
    cout << "Upsample success!\n";

}

//--------------------------------Cộng 2 tín hiệu ------------------------------------------

AudioSignal AudioSignal::operator+(const AudioSignal& other) const {
    vector<pair<double, double>> result;

    // Kiểm tra xem hai đối tượng có cùng tần số lấy mẫu không
    if (this->rate != other.rate) {
        cerr << "You can only add two signals at the same rate\n";
        // Trả về một đối tượng AudioSignal trống nếu không thể thực hiện phép cộng
        return AudioSignal(result, 0.0);
    }

    // Duyệt qua các mẫu của hai đối tượng và thực hiện phép cộng = 2 con trỏ 
    ll i = 0, j = 0;
    while (i < values.size() || j < other.values.size()) {
        if (i < values.size() && j < other.values.size()) {

            if (values[i].first == other.values[j].first) {
                // Thêm vào vector kết quả cặp giá trị âm thanh đã cộng
                result.push_back({ values[i].first, values[i].second + other.values[j].second });
                i++;
                j++;
            }
            else if (values[i].first < other.values[j].first) {
                // Nếu chỉ số thời gian của mẫu hiện tại của đối tượng thứ nhất nhỏ hơn
                // ta chỉ cần thêm mẫu đó vào vector kết quả
                result.push_back({ values[i].first, values[i].second });
                i++;
            }
            else {
                // Tương tự, nếu chỉ số thời gian của mẫu hiện tại của đối tượng thứ hai nhỏ hơn
                // ta chỉ cần thêm mẫu đó vào vector kết quả
                result.push_back({ other.values[j].first, other.values[j].second });
                j++;
            }
        }
        else if (i < values.size()) {
            // Nếu vẫn còn mẫu âm thanh của đối tượng thứ nhất chưa được xử lý
            result.push_back({ values[i].first, values[i].second });
            i++;
        }
        else {
            // Nếu vẫn còn mẫu âm thanh của đối tượng thứ hai chưa được xử lý
            result.push_back({ other.values[j].first, other.values[j].second });
            j++;
        }
    }

    cout << "The calculation is completed!\n";
    // Trả về một đối tượng AudioSignal mới chứa kết quả của phép cộng
    return AudioSignal(result, rate);
}


//--------------------------------Nhân 2 tín hiệu ------------------------------------------
AudioSignal AudioSignal::operator*(const AudioSignal& other) const {
    // Khởi tạo vector kết quả
    vector<pair<double, double>> result;

    // Kiểm tra xem hai tín hiệu có cùng tần số lấy mẫu không
    if (this->rate != other.rate) {
        // In ra thông báo lỗi nếu không cùng tần số
        cerr << "You can only multiply two signals at the same rate\n";
        // Trả về một đối tượng AudioSignal rỗng
        return AudioSignal(result, 0.0);
    }

    // Dùng hai biến i và j để duyệt qua các mẫu của hai tín hiệu
    long long i = 0, j = 0;

    // Duyệt qua các mẫu của hai tín hiệu
    while (i < values.size() || j < other.values.size()) {
        if (i < values.size() && j < other.values.size()) {
            // Nếu cùng thời điểm, thực hiện phép nhân và thêm vào kết quả
            if (values[i].first == other.values[j].first) {
                result.push_back({ values[i].first, values[i].second * other.values[j].second });
                i++;
                j++;
            }
            else if (values[i].first < other.values[j].first) {
                // Nếu thời điểm của mẫu đầu tiên nhỏ hơn, thêm vào kết quả với giá trị 0
                result.push_back({ values[i].first, 0 });
                i++;
            }
            else {
                // Nếu thời điểm của mẫu thứ hai nhỏ hơn, thêm vào kết quả với giá trị 0
                result.push_back({ other.values[j].first, 0 });
                j++;
            }
        }
        else if (i < values.size()) {
            // Nếu chỉ còn tín hiệu thứ nhất, thêm vào kết quả với giá trị 0
            result.push_back({ values[i].first, 0 });
            i++;
        }
        else {
            // Nếu chỉ còn tín hiệu thứ hai, thêm vào kết quả với giá trị 0
            result.push_back({ other.values[j].first, 0 });
            j++;
        }
    }

    // In ra thông báo khi tính toán hoàn tất
    cout << "The calculation is completed!\n";

    // Trả về một đối tượng AudioSignal mới với kết quả và cùng tần số lấy mẫu
    return AudioSignal(result, rate);
}

//--------------------------------Nhân tín hiệu với 1 số------------------------------------

AudioSignal AudioSignal::multiplyConstant(double constant) const {
    std::vector<std::pair<double, double>> result = this->values;
    for (long long i = 0; i < this->values.size(); i++) {
        result[i].second *= constant;
    }
    std::cout << "The calculation is completed!\n";
    return AudioSignal(result, rate);
}

//--------------------------------Tích chập ---------------------------------
AudioSignal AudioSignal::convolution(const AudioSignal& other) {
    int N = values.size();
    int M = other.values.size();
    std::vector<std::pair<double, double>> y(N + M - 1);

    for (int n = 0; n < N + M - 1; n++) {
        y[n].first = n / rate;
        for (int k = 0; k < M; k++) {
            if (n - k >= 0 && n - k < N) {
                y[n].second += values[n - k].second * other.values[k].second;
            }
        }
    }

    return AudioSignal{ y, rate };
}

//********************************BỘ LỌC TÍN HIỆU******************************************

//--------------------------------Low Pass Filter -----------------------------------------

void AudioSignal::LPF(long long fc, long long N, long long w) {
    double wc = 2 * pi * (fc / rate);

    // giá trị đầu vào
    vector <double> sn;
    for (int i = 0; i < values.size(); i++) {
        sn.push_back(values[i].second);
    }
    // yn = hd * sn
    // hd = hn * wn

    vector < double> hd;
    vector < double> yn;

    // tinh hn
    vector < double> hn;
    for (long long i = 0; i <= N - 1; i++) {
        double hi;
        hi = (wc / pi) * WSin(wc, i, N);

        hn.push_back(hi);
    }
    switch (w)
    {
    case 1:
        // với cửa sổ chữ nhật, w(n) = 1 từ 0 đến N-1
        // => hd = hn * wn = hn * 1 trong khoảng từ 0 -> N-1
        hd = hn;
        yn = convolutionVector(hd, sn);
        break;
    case 2:
    {
        // với cửa sổ hanning , wn = 0.5 - 0.5 *  cos((2*pi*n)/(N-1)) trong khoảng 0 -> N-1
        // tính h(d) = h(n) nhân chập w(n) trong khoảng 0 -> N-1

        // tinh w_han
        vector <double> w_han;

        for (int i = 0; i < N - 1; i++) {
            double wi = 0.5 - 0.5 * cos((2 * pi * i) / (N - 1));
            w_han.push_back(wi);
        }

        // hd = hn * wn
        hd = convolutionVector(hn, w_han);

        //yn = hd * sn
        yn = convolutionVector(hd, sn);


        break;
    }
    case 3:
    {
        // với cửa sổ hamming , wn = 0.54 - 0.46 *  cos((2*pi*n)/(N-1)) trong khoảng 0 -> N-1
        // tính h(d) = h(n) nhân chập w(n) trong khoảng 0 -> N-1

        // tinh w_han
        vector <double> w_han;
        for (int i = 0; i < N - 1; i++) {
            double wi = 0.54 - 0.46 * cos((2 * pi * i) / (N - 1));
            w_han.push_back(wi);
        }

        // hd = hn * wn
        hd = convolutionVector(hn, w_han);

        //yn = hd * sn
        yn = convolutionVector(hd, sn);


        break;
    }
    default:
        break;
    }

    // yn là dãy giá trị sau khi đã qua filter, gán lại cho giá trị của tín hiệu

    for (int i = 0; i < values.size(); i++) {
        values[i].second = yn[i];
    }

}


//--------------------------------High pass filter------------------------------------------
void AudioSignal::HPF(long long fc, long long N, long long w) {
    double wc = 2 * pi * (fc / rate);
    // u ( n - ((N-1)/2) ) = 1 nếu n - ((N-1)/2) = 0, bằng 0 nếu ngược lại

    //hn = u ( n - ((N-1)/2) )  - (wc / pi) * (sin(wc * (i - (N - 1) / 2)) / (wc * (i - (N - 1) / 2))) )

    // giá trị đầu vào
    vector <double> sn;
    for (int i = 0; i < values.size(); i++) {
        sn.push_back(values[i].second);
    }

    // yn = hd * sn
    // hd = hn * wn
    //hn = un - ( wc/pi ) * WSin 
    vector < double> hd;
    vector < double> yn;


 

    // tinh hn
    vector <double> hn;
    for (long long i = 0; i <= N - 1; i++) {
        double hi;
        if (i == (N - 1) / 2) {
            hi =  1 - (wc / pi) * WSin(wc, i, N);
        }
        else {
            hi =  - (wc / pi) * WSin(wc, i, N);
        }
        
        hn.push_back(hi);
    }

    switch (w)
    {
    case 1:
        // với cửa sổ chữ nhật, w(n) = 1 từ 0 đến N-1
        // => hd = hn * wn = hn * 1 trong khoảng từ 0 -> N-1
        hd = hn;
        yn = convolutionVector(hd, sn);
        break;
    case 2:
    {
        // với cửa sổ hanning , wn = 0.5 - 0.5 *  cos((2*pi*n)/(N-1)) trong khoảng 0 -> N-1
        // tính h(d) = h(n) nhân chập w(n) trong khoảng 0 -> N-1

        // tinh w_han
        vector <double> w_han;
        for (int i = 0; i <= N - 1; i++) {
            double wi = 0.5 - 0.5 * cos((2 * pi * i) / (N - 1));
            w_han.push_back(wi);
        }

        // hd = hn * wn
        hd = convolutionVector(hn, w_han);

        //yn = hd * sn
        yn = convolutionVector(hd, sn);


        break;
    }
    case 3:
    {
        // với cửa sổ hamming , wn = 0.54 - 0.46 *  cos((2*pi*n)/(N-1)) trong khoảng 0 -> N-1
        // tính h(d) = h(n) nhân chập w(n) trong khoảng 0 -> N-1

        // tinh w_han
        vector <double> w_han;
        for (int i = 0; i <= N - 1; i++) {
            double wi = 0.54 - 0.46 * cos((2 * pi * i) / (N - 1));
            w_han.push_back(wi);
        }

        // hd = hn * wn
        hd = convolutionVector(hn, w_han);

        //yn = hd * sn
        yn = convolutionVector(hd, sn);


        break;
    }
    default:
        break;
    }

    // yn là dãy giá trị sau khi đã qua filter, gán lại cho giá trị của tín hiệu

    for (int i = 0; i < values.size(); i++) {
        values[i].second = yn[i];
    }

}

//--------------------------------Band Pass Filter -----------------------------------------
void AudioSignal::BPF(long long fc1, long long fc2, long long N, long long w) {

    double wc1 = (2 * pi * fc1) / rate;
    double wc2 = (2 * pi * fc2) / rate;

    // giá trị đầu vào
    vector <double> sn;
    for (int i = 0; i < values.size(); i++) {
        sn.push_back(values[i].second);
    }
    // cần tính yn
    // yn = hd * sn
    // hd = hn * wn
    vector < double> hd;
    vector < double> yn;

    // tinh hn
    vector < double> hn;
    for (long long i = 0; i <= N - 1; i++) {
        double hi;
        hi = (wc2 / pi) * WSin(wc2, i, N) - (wc1 / pi) * WSin(wc1, i, N);

        hn.push_back(hi);
    }

    switch (w)
    {
    case 1:
        // với cửa sổ chữ nhật, w(n) = 1 từ 0 đến N-1
        // => hd = hn * wn = hn * 1 trong khoảng từ 0 -> N-1
        hd = hn;
        yn = convolutionVector(hd, sn);
        break;
    case 2:
    {
        // với cửa sổ hanning , wn = 0.5 - 0.5 *  cos((2*pi*n)/(N-1)) trong khoảng 0 -> N-1
        // tính h(d) = h(n) nhân chập w(n) trong khoảng 0 -> N-1

        // tinh w_han
        vector <double> w_han;
        for (int i = 0; i < N - 1; i++) {
            double wi = 0.5 - 0.5 * cos((2 * pi * i) / (N - 1));
            w_han.push_back(wi);
        }

        // hd = hn * wn
        hd = convolutionVector(hn, w_han);

        //yn = hd * sn
        yn = convolutionVector(hd, sn);


        break;
    }
    case 3:
    {
        // với cửa sổ hamming , wn = 0.54 - 0.46 *  cos((2*pi*n)/(N-1)) trong khoảng 0 -> N-1
        // tính h(d) = h(n) nhân chập w(n) trong khoảng 0 -> N-1

        // tinh w_han
        vector <double> w_han;
        for (int i = 0; i < N - 1; i++) {
            double wi = 0.54 - 0.46 * cos((2 * pi * i) / (N - 1));
            w_han.push_back(wi);
        }

        // hd = hn * wn
        hd = convolutionVector(hn, w_han);

        //yn = hd * sn
        yn = convolutionVector(hd, sn);


        break;
    }
    default:
        break;
    }

    // yn là dãy giá trị sau khi đã qua filter, gán lại cho giá trị của tín hiệu

    for (int i = 0; i < values.size(); i++) {
        values[i].second = yn[i];
    }

}

//--------------------------------Band Stop Filter -----------------------------------------
void AudioSignal::BSF(long long fc1, long long fc2, long long N, long long w) {

    double wc1 = 2 * pi * (fc1 / rate);
    double wc2 = 2 * pi * (fc2 / rate);
    // u ( n - ((N-1)/2) ) = 1 nếu n - ((N-1)/2) = 0, bằng 0 nếu ngược lại

    //hn = u ( n - ((N-1)/2) )  - (wc / pi) * (sin(wc * (i - (N - 1) / 2)) / (wc * (i - (N - 1) / 2))) )

    // giá trị đầu vào
    vector <double> sn;
    for (int i = 0; i < values.size(); i++) {
        sn.push_back(values[i].second);
    }

    // yn = hd * sn
    // hd = hn * wn
    vector < double> hd;
    vector < double> yn;
    // Dãy xung đơn vị 
  



    // tinh hn
    vector < double> hn;
    for (long long i = 0; i <= N - 1; i++) {
        double hi;
        if (i == (N - 1) / 2) {
            hi = 1 - ((wc2 / pi) * WSin(wc2, i, N) - (wc1 / pi) * WSin(wc1, i, N));
        }
        else {
            hi =  - ((wc2 / pi) * WSin(wc2, i, N) - (wc1 / pi) * WSin(wc1, i, N));
        }
        hn.push_back(hi);
    }

    switch (w)
    {
    case 1:
        // với cửa sổ chữ nhật, w(n) = 1 từ 0 đến N-1
        // => hd = hn * wn = hn * 1 trong khoảng từ 0 -> N-1
        hd = hn;
        yn = convolutionVector(hd, sn);
        break;
    case 2:
    {
        // với cửa sổ hanning , wn = 0.5 - 0.5 *  cos((2*pi*n)/(N-1)) trong khoảng 0 -> N-1
        // tính h(d) = h(n) nhân chập w(n) trong khoảng 0 -> N-1

        // tinh w_han
        vector <double> w_han;
        for (int i = 0; i <= N - 1; i++) {
            double wi = 0.5 - 0.5 * cos((2 * pi * i) / (N - 1));
            w_han.push_back(wi);
        }

        // hd = hn * wn
        hd = convolutionVector(hn, w_han);

        //yn = hd * sn
        yn = convolutionVector(hd, sn);


        break;
    }
    case 3:
    {
        // với cửa sổ hamming , wn = 0.54 - 0.46 *  cos((2*pi*n)/(N-1)) trong khoảng 0 -> N-1
        // tính h(d) = h(n) nhân chập w(n) trong khoảng 0 -> N-1

        // tinh w_han
        vector <double> w_han;
        for (int i = 0; i <= N - 1; i++) {
            double wi = 0.54 - 0.46 * cos((2 * pi * i) / (N - 1));
            w_han.push_back(wi);
        }

        // hd = hn * wn
        hd = convolutionVector(hn, w_han);

        //yn = hd * sn
        yn = convolutionVector(hd, sn);


        break;
    }
    default:
        break;
    }

    // yn là dãy giá trị sau khi đã qua filter, gán lại cho giá trị của tín hiệu

    for (int i = 0; i < values.size(); i++) {
        values[i].second = yn[i];
    }

}


//********************************EFFECT****************************************************

//--------------------------------Sound Effext: Echo ---------------------------------------
void AudioSignal::Echo(double M, double ak)  {

    //s[n-k] -> k ( 1-> M)
    vector<pair<double, double>> tmp = timeShiftVector(values , 1 );

    for (long long k = 2; k <= M; k++) {
        tmp =  sumVector(tmp, timeShiftVector(values, k));
    }
    // ak * s[n-k]
    
    vector<pair<double, double>> tmp2 ( tmp.size());

    for (long long i = 0; i < tmp2.size(); i++) {
        tmp2[i].second = ak * tmp[i].second;
        tmp2[i].first = tmp[i].first;
    }

    //y[n] = s[n] + ak * s[n-k] with k : 1-> M

    vector<pair<double, double>> yn;
    yn = sumVector(values, tmp2);

    values = yn;
}

//--------------------------------Sound Effext: Fade----------------------------------------


void AudioSignal::FadeIn()  {

    std::vector <std::pair< double, double >> x (values.size());

    for (long long i = 0; i < x.size(); i++) {
        x[i].first = values[i].first;

        if (values[i].first >= 0) {
            x[i].second = values[i].first;
        }
        else {
            x[i].second = 0;
        }
        
    }   
    values = mulVector(values, x);
}

void AudioSignal::FadeOut() {

    std::vector <std::pair< double, double >> x(values.size());
    std::vector <double> tmp;
    for (long long i = 0; i < values.size(); i++) {
        tmp.push_back(values[i].first);
    }
    reverse(tmp.begin(), tmp.end());

    for (int i = 0; i < x.size(); i++) {
        x[i].first = values[i].first;
        if (values[i].first >= 0) {
            x[i].second = tmp[i];
        }
        else {
            x[i].second = 0;
        }
    }

    values = mulVector(values, x);
}

//--------------------------------Sound Effext: Reverb--------------------------------------

void AudioSignal::Reverb( AudioSignal& other, ll g, ll D)  {
    // s[n]
    vector < pair<double, double >> sn = values;
    //-g * s[n]
    for (long long i = 0; i < sn.size(); i++) {
        sn[i].second = sn[i].second * (g * -1);
    }
    //s[n-D]
    vector<pair<double, double>> sn1 = timeShiftVector(values, D);
    // ( 1- g * g ) * s[n-D]
    for (long long i = 0; i < sn1.size(); i++) {
        sn1[i].second = sn1[i].second * (1 - g * g);
    }
    //x[n-D]
    vector < pair<double, double >> x = timeShiftVector(other.getValues(), D);
    //( 1- g ) * g * x[n - D]
    for (long long i = 0; i < x.size(); i++) {
        x[i].second = x[i].second * (g * (1 - g * g));
    }

    vector < pair<double, double >> yn;
    yn = sumVector(sn, sn1);
    yn = sumVector(yn, x);

    values = yn;
}

//--------------------------------vẽ biểu đồ tín hiệu --------------------------------------



//******************************Hàm Set Get *************************************************

std::vector<std::pair<double, double>> AudioSignal::getValues() {
    return this->values;
}

void AudioSignal::setValues(std::vector<std::pair<double, double>> values) {
    this->values = values;
}

double AudioSignal::getRate() {
    return this->rate;
}

void AudioSignal::setRate(double rate) {
    this->rate = rate;
}


// ghi file -----------------------------------------------------------------------------------
void writeToFile(std::ofstream& file, int value, int size) {
    file.write(reinterpret_cast<const char*> (&value), size);
}

void AudioSignal::writeWavFile(WavHeader refWavHeader) {

    if (values == std::vector<std::pair<double, double>>{}) {
        std::cout << "You have no data to save!\n";
        return;
    }

    std::cin.get();
    std::cout << "Enter the audio file name: ";
    std::string name;
    std::getline(std::cin, name);
    std::string filename = "../assets/" + name + ".wav";

    std::ofstream outFile(filename, std::ios::binary);

    if (!outFile.is_open()) {
        std::cerr << "Cannot open file to write data." << std::endl;
        return;
    }

    //Header chunk
    outFile << "RIFF";
    outFile << "----";
    outFile << "WAVE";

    //Format chunk
    outFile << "fmt ";
    writeToFile(outFile, 16, 4); //Length of format data as listed above
    writeToFile(outFile, 1, 2); //Type of format (1 is PCM) - 2 byte integer
    writeToFile(outFile, refWavHeader.numChannels, 2); //Number of Channels - 2 byte integer
    writeToFile(outFile, rate, 4); //Sample Rate - 32 byte integer
    writeToFile(outFile, (rate * refWavHeader.bitsPerSample * refWavHeader.numChannels) / 8, 4); //Byte rate
    writeToFile(outFile, (refWavHeader.bitsPerSample * refWavHeader.numChannels) / 8, 2); //Block align (bytes/sample)
    writeToFile(outFile, refWavHeader.bitsPerSample, 2); //Bits per sample

    //Date chunk
    outFile << "data";
    outFile << "----";
    int preAudioPosition = outFile.tellp();

    for (const auto& sample : values) {
        int16_t sampleValue = static_cast<int16_t>(sample.second);
        writeToFile(outFile, sampleValue, 2);
    }

    int posAudioPosition = outFile.tellp();
    outFile.seekp(preAudioPosition - 4);
    writeToFile(outFile, posAudioPosition - preAudioPosition, 4);

    outFile.seekp(4, std::ios::beg);
    writeToFile(outFile, posAudioPosition - 8, 4);

    outFile.close();

    std::cout << "File WAV '" << filename << "' was recorded successfully." << std::endl;
}
//---------------------------------Bộ lọc thông thấp Low Pass Filter ------------------------------------------------------------
//yêu cầu người nhập nhập vào tần số cắt: fc, nhập bậc của bộ lọc : N

//***************************************CÁC HÀM BỔ TRỢ****************************************

// Hàm nhân chập cho 2 vector giá trị
std::vector<double> AudioSignal::convolutionVector(const std::vector<double>& x, const std::vector<double>& h) {
    int N = x.size();
    int M = h.size();
    std::vector<double> y(N + M - 1, 0.0);

    for (int n = 0; n < N + M - 1; n++) {
        for (int k = 0; k < M; k++) {
            if (n - k >= 0 && n - k < N) {
                y[n] += x[n - k] * h[k];
            }
        }
    }

    return y;
}


//tính đoạn công thức có sin ------------------------------------------------------------------------

double AudioSignal::WSin(double wc, long long n, long long N ) {

  
    double mauso = (wc * (n - (N - 1) / 2));
    double res = 0;
    if (mauso == 0) {
        res = 1;
    }
    else {
        res = (sin(wc * (n - (N - 1) / 2)) / (wc * (n - (N - 1) / 2)));
    }

    return res;
}

//Hàm nhân 2 vector pair
std::vector <std::pair< double, double >>AudioSignal::mulVector(const std::vector <std::pair< double, double >>& x, const  std::vector <std::pair< double, double >>& h) {

    // Khởi tạo vector kết quả
    vector<std::pair<double, double>> result;

    // Dùng hai biến i và j để duyệt qua các mẫu của hai tín hiệu
    long long i = 0, j = 0;

    // Duyệt qua các mẫu của hai tín hiệu
    while (i < x.size() || j < h.size()) {
        if (i < x.size() && j < h.size()) {
            // Nếu cùng thời điểm, thực hiện phép nhân và thêm vào kết quả
            if (x[i].first == h[j].first) {
                result.push_back({ x[i].first, x[i].second * h[j].second });
                i++;
                j++;
            }
            else if (x[i].first < h[j].first) {
                // Nếu thời điểm của mẫu đầu tiên nhỏ hơn, thêm vào kết quả với giá trị 0
                result.push_back({ x[i].first, 0 });
                i++;
            }
            else {
                // Nếu thời điểm của mẫu thứ hai nhỏ hơn, thêm vào kết quả với giá trị 0
                result.push_back({ h[j].first, 0 });
                j++;
            }
        }
        else if (i < x.size()) {
            // Nếu chỉ còn tín hiệu thứ nhất, thêm vào kết quả với giá trị 0
            result.push_back({ x[i].first, 0 });
            i++;
        }
        else {
            // Nếu chỉ còn tín hiệu thứ hai, thêm vào kết quả với giá trị 0
            result.push_back({ h[j].first, 0 });
            j++;
        }
    }
    return result;

}

//Hàm cộng 2 vector pair
std::vector <std::pair< double, double >>AudioSignal::sumVector(const std::vector <std::pair< double, double >>& x, const  std::vector <std::pair< double, double >>& h) {

    vector<pair<double, double>> result;

    // Duyệt qua các mẫu của hai đối tượng và thực hiện phép cộng = 2 con trỏ 
    ll i = 0, j = 0;
    while (i < x.size() || j < h.size()) {
        if (i < x.size() && j < h.size()) {

            if (x[i].first == h[j].first) {
                // Thêm vào vector kết quả cặp giá trị âm thanh đã cộng
                result.push_back({ x[i].first, x[i].second + h[j].second });
                i++;
                j++;
            }
            else if (x[i].first < h[j].first) {
                // Nếu chỉ số thời gian của mẫu hiện tại của đối tượng thứ nhất nhỏ hơn
                // ta chỉ cần thêm mẫu đó vào vector kết quả
                result.push_back({ x[i].first, x[i].second });
                i++;
            }
            else {
                // Tương tự, nếu chỉ số thời gian của mẫu hiện tại của đối tượng thứ hai nhỏ hơn
                // ta chỉ cần thêm mẫu đó vào vector kết quả
                result.push_back({ h[j].first, h[j].second });
                j++;
            }
        }
        else if (i < x.size()) {
            // Nếu vẫn còn mẫu âm thanh của đối tượng thứ nhất chưa được xử lý
            result.push_back({ x[i].first, x[i].second });
            i++;
        }
        else {
            // Nếu vẫn còn mẫu âm thanh của đối tượng thứ hai chưa được xử lý
            result.push_back({ h[j].first, h[j].second });
            j++;
        }
    }

    return result;

}

