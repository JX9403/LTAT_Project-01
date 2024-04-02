#include <iostream>
#include<vector>
#include<numeric>
#include<random>
#include<string>
#include"gnuplot-iostream.h"
#include"AudioSignal.h"
#include"Wav.h"
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<Windows.h>
#include<sndfile.h>
#include<sndfile.hh>

AudioSignal audioSignal1({}, 0);
AudioSignal audioSignal2({}, 0);
Wav wav;
bool save = false;

// Hàm saveSignal : sử dụng biến save để xác nhận người dùng có muốn mở file mới không
// ban đầu biến save luôn false, nếu chọn yes => save = true, tại các hàm sao, nếu save = true thì 
// không cần mở file wav mới nữa

void saveSignal() {
    char s = 'n';
    std::cout << "Do you want to save this audio signal for the next operation?\n";
    std::cout << "y(Yes) / n(No)\n";
    std::cout << "select: ";
    std::cin >> s;
    if (s == 'y') {
        save = true;
    }
    else {
        save = false;
    }
}
void plot() {
    char s = '1';
    std::cout << "Do you want to graph this signal?\n";
    std::cout << "y(Yes) / n(No)\n";
    std::cout << "select: ";
    std::cin >> s;
    if (s == 'y') {
        // đọc ký tự enter
        std::cin.get();

        // vẽ biểu đồ
        audioSignal1.drawPlot();
    }



}

bool openWavFile(AudioSignal& refAudioSignal){

    std::string filePath;
    char fileNameBuffer[MAX_PATH] = "";

    // Tạo một cấu trúc để chứa thông tin về loại file
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = fileNameBuffer;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Audio Files (*.wav)\0*.wav\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Hiển thị hộp thoại chọn file
    if (GetOpenFileNameA(&ofn))
    {
        filePath = fileNameBuffer;
        sf::SoundBuffer buffer;

        // Nạp file .wav vào SoundBuffer
        if (!buffer.loadFromFile(filePath))
        {
            std::cout << "Error: Cannot open file " << filePath << std::endl;
            return false;
        }

        wav = Wav(filePath);
        refAudioSignal = AudioSignal(wav.toSignals(), wav.getSampleRate());

        return true;
    }
    else
    {
        std::cout << "Cancel file selection" << std::endl;
        return false;
    }
}

void timeShifting() {

    if (!save) {
        openWavFile(audioSignal1);
    }

    long long m;
    std::cout << "Choose m = ";
    std::cin >> m;
    audioSignal1.timeShift(m);

    saveSignal();
    plot();
}

void reversal() {

    if (!save) {
        openWavFile(audioSignal1);
    }
    audioSignal1.reverseTime();
    saveSignal();
    plot();
}

void signalSum() {
    if (!save) {
        std::cout << "Select signal file 1\n";
        openWavFile(audioSignal1);
    }
    std::cout << "Select signal file 2\n";
    openWavFile(audioSignal2);

    audioSignal1 = audioSignal1 + audioSignal2;

    saveSignal();
    plot();
}

void signalMultiply() {
    if (!save) {
        std::cout << "Select signal file 1\n";
        openWavFile(audioSignal1);
    }
    std::cout << "Select signal file 2\n";
    openWavFile(audioSignal2);

    audioSignal1 = audioSignal1 * audioSignal2;

    saveSignal();
    plot();
}

void signalMultiplyConstant() {
    if (!save) {
        openWavFile(audioSignal1);
    }

    long long constant;
    std::cout << "Choose constant = ";
    std::cin >> constant;
    audioSignal1 = audioSignal1.multiplyConstant(constant);

    saveSignal();
    plot();
}

void Downsampling() {
    if (!save) {
        openWavFile(audioSignal1);
    }

    int M;
    std::cout << "Choose M = ";
    std::cin >> M;
    audioSignal1.downsample(M);

    saveSignal();
    plot();
}

void Upsampling() {
    if (!save) {
        openWavFile(audioSignal1);
    }

    int L;
    std::cout << "Choose L = ";
    std::cin >> L;
    audioSignal1.upsample(L);

    saveSignal();
    plot();
}


void convolution() {
    if (!save) {
        std::cout << "Select signal file 1\n";
        openWavFile(audioSignal1);
    }
    std::cout << "Select signal file 2\n";
    openWavFile(audioSignal2);

    audioSignal1 = audioSignal1.convolution(audioSignal2);

    saveSignal();
    plot();
}

void drawDiagram() {
    openWavFile(audioSignal1);
    plot();
}

void playSound() {
    openWavFile(audioSignal2);
    wav.playWav();
}


void LPF() {
    if (!save) {
        std::cout << "Select signal file 1\n";
        openWavFile(audioSignal1);
    }
    long long fc, N, w;
    std::cout << " Choose fc ( cut-off frequency) = ";
    std::cin >> fc;
    std::cout << " Choose N  = ";
    std::cin >> N;
    std::cout << "1. Rect Window \n";
    std::cout << "2. Hanning Window \n";
    std::cout << "3. Hamming Window \n";
    std::cout << " Choose window  = ";

    std::cin >> w;

    audioSignal1.LPF(fc, N, w);

    saveSignal();
    plot();
}

void HPF() {
    if (!save) {
        std::cout << "Select signal file 1\n";
        openWavFile(audioSignal1);
    }
    long long fc, N, w;
    std::cout << " Choose fc ( cut-off frequency) = ";
    std::cin >> fc;
    std::cout << " Choose N  = ";
    std::cin >> N;
    std::cout << "1. Rect Window \n";
    std::cout << "2. Hanning Window \n";
    std::cout << "3. Hamming Window \n";
    std::cout << " Choose window  = ";

    std::cin >> w;

    audioSignal1.HPF(fc, N, w);

    saveSignal();
    plot();
}

void BPF() {
    if (!save) {
        std::cout << "Select signal file 1\n";
        openWavFile(audioSignal1);
    }
    long long fc1, fc2, N, w;
    std::cout << " Choose fc1 ( cut-off frequency) = ";
    std::cin >> fc1;
    std::cout << " Choose fc2 ( cut-off frequency) = ";
    std::cin >> fc2;
    std::cout << " Choose N  = ";
    std::cin >> N;
    std::cout << "1. Rect Window \n";
    std::cout << "2. Hanning Window \n";
    std::cout << "3. Hamming Window \n";
    std::cout << " Choose window  = ";

    std::cin >> w;

    audioSignal1.BPF(fc1, fc2, N, w);

    saveSignal();
    plot();
}

void BSF() {
    if (!save) {
        std::cout << "Select signal file 1\n";
        openWavFile(audioSignal1);
    }
    long long fc1, fc2, N, w;
    std::cout << " Choose fc1 ( cut-off frequency) = ";
    std::cin >> fc1;
    std::cout << " Choose fc2 ( cut-off frequency) = ";
    std::cin >> fc2;
    std::cout << " Choose N  = ";
    std::cin >> N;
    std::cout << "1. Rect Window \n";
    std::cout << "2. Hanning Window \n";
    std::cout << "3. Hamming Window \n";
    std::cout << " Choose window  = ";

    std::cin >> w;

    audioSignal1.BPF(fc1, fc2, N, w);

    saveSignal();
    plot();
}

void Echo() {
    openWavFile(audioSignal1);
    long long M;
    std::cout << "Choose M = ";
    std::cin >> M;
    double ak;
    std::cout << "Choose ak ( -1 < ak < 1 ) = ";
    std::cin >> ak;
    audioSignal1.Echo(M, ak);
   
    plot();
}


void FadeIn() {
    openWavFile(audioSignal1);
    audioSignal1.FadeIn();
    plot();
}

void FadeOut() {
    openWavFile(audioSignal1);
    audioSignal1.FadeOut();
    plot();
}

void Increase() {
    if (!save) {
        openWavFile(audioSignal1);
    }

    double constant;
    std::cout << "Choose n ( n > 1 )  = ";
    std::cin >> constant;
    audioSignal1 = audioSignal1.multiplyConstant(constant);
    saveSignal();
    plot();
}

void Decrease() {
    if (!save) {
        openWavFile(audioSignal1);
    }
    double constant;
    std::cout << "Choose n ( 0 < n < 1 )  = ";
    std::cin >> constant;
    audioSignal1 = audioSignal1.multiplyConstant(constant);
    saveSignal();
    plot();
}

void Reverb() {
    openWavFile(audioSignal1);
    openWavFile(audioSignal2);
    long long g;
    std::cout << "Choose g = ";
    std::cin >> g;
    long long D;
    std::cout << "Choose D = ";
    std::cin >> D;
    audioSignal1.Reverb(audioSignal2, g, D);
    plot();
}

int main()
{  
    bool flag = true;
    while (flag) {
        int select;
        std::cout << "_____________MINI_PROJECT_SOUND_PROGRAMING_1_____________\n";
        std::cout << "              1. Time shifting\n";
        std::cout << "              2. Time reversal\n";
        std::cout << "              3. Downsampling\n";
        std::cout << "              4. Upsampling\n";
        std::cout << "              5. Sum two signals\n";
        std::cout << "              6. Multiply two signals\n";
        std::cout << "              7. Multiply signal with a number\n";
        std::cout << "              8. Convolve signals\n";
        std::cout << "              9.Low Pass Filter\n";
        std::cout << "              10.High Pass Filter\n";
        std::cout << "              11.Band Pass Filter\n";
        std::cout << "              12.Band Stop Filter\n";
        std::cout << "              13.Echo effect\n";
        std::cout << "              14.Fade in\n";        
        std::cout << "              15.Fade out\n";
        std::cout << "              16.Increase\n";
        std::cout << "              17.Decrease\n";
        std::cout << "              18.Reverb\n";
        std::cout << "              19.Draw diagram\n";
        std::cout << "              20.Play sound\n";
        std::cout << "              21.Save file\n";
        std::cout << "              0. Quit\n";
        std::cout << "__________________________________________________________\n";
        std::cout << "Select: ";
        std::cin >> select;
        
        switch (select)
        {
        case 1:
            timeShifting();
            break;
        case 2:
            reversal();
            break;
        case 3:
            Downsampling();
            break;
        case 4:
             Upsampling();
            break;
        case 5:
            signalSum();
            break;
        case 6:
             signalMultiply();
            break;
        case 7:
            signalMultiplyConstant();
            break;
        case 8:
            convolution();
            break;
        case 9:
            LPF();
            break;
        case 10:
            HPF();
            break;
        case 11:
            BPF();
            break;
        case 12:
            BSF();
            break;
        case 13:
            Echo();
            break;
        case 14:
            FadeIn();
            break;
        case 15:
            FadeOut();
            break;
        case 16:
            Increase();
            break;
        case 17:
            Decrease();
            break;
        case 18:
            Reverb();
            break;
        case 19:
            drawDiagram();
            break;
        case 20:
            playSound();
            break;
        case 21:
            audioSignal1.writeWavFile(wav.getWavHeader());
            break;
        case 0:
            flag = false;
            break;
        default :
            break;
        }
    }


    return 0;
}
