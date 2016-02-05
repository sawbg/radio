#include <complex>
#include <functional>
#include <iostream>
#include <valarray>

const double PI = 3.141592653589793238460;

typedef std::valarray<std::complex<double>> CArray;

/**
 * This code was taken from
 * http://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B.
 */

// Cooley-Tukey FFT (in-place, breadth-first, decimation-in-frequency)
// Better optimized but less intuitive
void fft(CArray &x)
{
	// DFT
	unsigned int N = x.size(), k = N, n;
	double thetaT = 3.14159265358979323846264338328L / N;
	std::complex<double> phiT(cos(thetaT), sin(thetaT)), T;
	while (k > 1)
	{
		n = k;
		k >>= 1;
		phiT = phiT * phiT;
		T = 1.0L;
		for (unsigned int l = 0; l < k; l++)
		{
			for (unsigned int a = l; a < N; a += n)
			{
				unsigned int b = a + k;
				std::complex<double> t = x[a] - x[b];
				x[a] += x[b];
				x[b] = t * T;
			}
			T *= phiT;
		}
	}
	// Decimate
	unsigned int m = (unsigned int)log2(N);
	for (unsigned int a = 0; a < N; a++)
	{
		unsigned int b = a;
		// Reverse bits
		b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
		b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
		b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
		b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
		b = ((b >> 16) | (b << 16)) >> (32 - m);
		if (b > a)
		{
			std::complex<double> t = x[a];
			x[a] = x[b];
			x[b] = t;
		}
	}
	//// Normalize (This section make it not working correctly)
	//std::complex<double> f = 1.0 / sqrt(N);
	//for (unsigned int i = 0; i < N; i++)
	//	x[i] *= f;
}

// inverse fft (in-place)
void ifft(CArray& x)
{
	// conjugate the complex numbers
	x = x.apply(std::conj);

	// forward fft
	fft( x );

	// conjugate the complex numbers again
	x = x.apply(std::conj);

	// scale the numbers
	x /= x.size();
}

std::complex<double> hilbert(std::complex<double> n) {
	return std::complex<double>(-2 * n.imag(), 0);
}

int main()
{
	const std::complex<double> test[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	CArray data(test, 16);

	// forward fft
	fft(data);

	std::cout << "fft" << std::endl;
	for (int i = 0; i < 16; ++i)
	{
	//	std::cout << data[i] << std::endl;
	}

	for(int i = 8; i < 16; i++) {
		data[i] = 0;
	}

	// inverse fft
	ifft(data);
	std::cout << std::endl << "ifft" << std::endl;

	for (int i = 0; i < 16; ++i)
	{
	//	std::cout << data[i] << std::endl;
	}

	data = data.apply(hilbert);

	std::cout << std::endl;

	for(int i = 0; i < 16; i++) {
		std::cout << data[i].real() << std::endl;
	}

	return 0;
}
