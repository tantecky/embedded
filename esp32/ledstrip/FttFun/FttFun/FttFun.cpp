
#include <cstdio>
#include <cassert>
#include <cmath>
#include <complex>
#include <chrono>
#include <numeric>
#include "FftFun.hpp"
#include "SinCosTable.hpp"
#include "rfft.hpp"

constexpr int N = sizeof(Data) / sizeof(float);
//constexpr int N = 8;
constexpr int N_HALF = N / 2;
const int M = int(log(N) / log(2));

SinCosTable SinCos(N, M);

inline bool approx(float a, float b, float epsilon = 1)
{
	return fabs(a - b) <= epsilon;
}

// returns non-symmetric Hann window of size n
const float* createHann(const int n)
{
	// n + 1 because non-symmetric
	const int n1 = n + 1;
	float* w = new float[n1];

	for (size_t i = 0; i < n1; i++)
	{
		w[i] = 0.5f - 0.5f * cosf((2.0f * M_PI_F * i) / n);
	}

	return w;
}

int main()
{
	// N = 2 ** M 
	//  Re(0), Re(1), ..., Re(n/2), Im(N/2-1), ..., Im(1)
	SinCos.init();

	std::complex<float> nums[N_HALF + 1] = { 0 };

	auto start = std::chrono::steady_clock::now();
	rfft(Data, N, M);
	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	printf("%lld us\n", elapsed.count());

	nums[0].real(Data[0]);

	for (size_t i = 1; i <= N_HALF; i++)
	{
		nums[i].real(Data[i]);
	}

	for (size_t i = 1; i <= N_HALF - 1; i++)
	{
		nums[i].imag(Data[N - i]);
	}

	//for (auto& v : nums) {
	//	printf("%f %fi\n", v.real(), v.imag());
	//}

	std::complex<float> sum(0, 0);
	sum = std::accumulate(nums, nums + N_HALF + 1, sum);

	printf("SUM:\n");

	printf("%f %fi\n", sum.real(), sum.imag());
	assert(approx(sum.real(), 261632.0f));
	assert(approx(sum.imag(), 1062055.67936177f));

	//mag2(Data, N);

	//float sumMag2 = 0;
	//for (int i = 0; i < N_HALF + 1; i++)
	//{
	//	sumMag2 += Data[i];

	//}
	//printf("SUM MAG**2: %f\n", sumMag2);
	//assert(sumMag2, 320154370048.0f);

	mag(Data, N);

	float sumMag = 0;
	for (int i = 0; i < N_HALF + 1; i++)
	{
		sumMag += Data[i];

	}
	printf("SUM MAG: %f\n", sumMag);
	assert(sumMag, 1701764.342344414f);

	const float* w = createHann(N);

	printf("%e %e %e %e\n", w[0], w[1], w[2], w[1023]);
}
