#pragma once
#include "gnuplot-iostream.h"
#include "wav.h"

class AudioSignal
{
public:
	// Hàm khởi tạo
	AudioSignal(std::vector<std::pair<double, double>> values, double sampling_rate);
	
	// Các phép toán cơ bản trên tín hiệu
	void timeShift(long long m) ;
	std::vector<std::pair<double, double>> timeShiftVector(std::vector<std::pair<double, double>> values, long long m);
	void reverseTime();
	void downsample(int M);
	void upsample(int L);

	AudioSignal operator+(const AudioSignal& other) const;
	AudioSignal operator*(const AudioSignal& other) const;
	AudioSignal multiplyConstant(double constant) const;

	AudioSignal convolution(const AudioSignal& other);
	
	//Bộ lọc tín hiệu

	void LPF(long long fc, long long N, long long w);
	void HPF(long long fc, long long N, long long w);
	void BPF(long long fc1, long long fc2, long long N, long long w);
	void BSF(long long fc1, long long fc2, long long N, long long w);

	// Hàm effect 
	
	void Echo(double M, double ak) ;

	void FadeIn();
	void FadeOut();

	void Reverb( AudioSignal& other, long long g, long long D) ;

	// Hàm vẽ 
	void drawPlot() const;

	// Hàm ghi file 
	void writeWavFile(WavHeader refWavHeader);

	// Hàm get set
	std::vector<std::pair<double, double>> getValues();
	void setValues(std::vector<std::pair<double, double>> values);
	double getRate();
	void setRate(double rate);

	// Hàm bổ trợ

	// Hàm tính công thức có sin
	double WSin( double wc, long long n, long long N);
	// Hàm tích chập đầu vào là vector pair
	std::vector<double> convolutionVector(const std::vector<double>& x, const std::vector<double>& h);
	std::vector <std::pair< double, double >>mulVector(const std::vector <std::pair< double, double >>& x, const std::vector <std::pair< double, double >>& h);
	std::vector <std::pair< double, double >>sumVector(const std::vector <std::pair< double, double >>& x, const std::vector <std::pair< double, double >>& h);

private:
	std::vector<std::pair<double, double>> values = {};
	double rate = 0;
};