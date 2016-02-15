/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Tests FFT, IFFT, and Hilbert implementations in zdomain.hpp.
 */

#include <complex>
#include <iostream>

#include "definitions.hpp"
#include "zdomain.hpp"

using namespace radio;

/**
 * This program tests the fft(), ifft(), and hilbert() functions in the
 * zdomain.hpp file.
 *
 * This code is based on code from
 * http://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B.
 */
int main()
{
	std::complex<float32> test[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	float32 ftest[16];	
	float32 dest[16];

	for(int i = 0; i < 16; i++) {
		ftest[i] = test[i].real();
	}

	// forward fft
	fft(test, 16);

	std::cout << "fft" << std::endl;

	for (int i = 0; i < 16; ++i)
	{
	//	std::cout << test[i] << std::endl;
	}

	// inverse fft
	ifft(test, 16);
	std::cout << std::endl << "ifft" << std::endl;

	for (int i = 0; i < 16; ++i)
	{
		std::cout << test[i] << std::endl;
	}

	hilbert(ftest, dest, 16);
	std::cout << std::endl << "hilbert" << std::endl;

	for(int i = 0; i < 16; i++) {
		std::cout << dest[i] << std::endl;
	}

	return 0;
}
