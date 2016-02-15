/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains the functions to manipulate sequential data in the frequency
 * (z) domain.
 */

#ifndef zdomain_H
#define zdomain_H

#include <complex>

#include "definitions.hpp"

namespace radio {

	/**
	 * Replaces the values in an array of complex float32's with their respective
	 * conjugates.
	 *
	 * @param data the array whose values should be replaced with their
	 * respective conjugates
	 *
	 * @param size the number of elements in the data array 
	 */
	void aconj(cfloat32* data, uint32 size);

	/**
	 * Replaces the values of an array of cfloat32's with the array's DFT using
	 * a decimation-in-frequency algorithm.
	 *
	 * This code is based on code from
	 * http://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B.
	 *
	 * @param data the array whose values should be replaced with its DFT
	 *
	 * @param size the number of elements in the data array
	 */
	void fft(cfloat32* data, uint32 size);

	/**
	 * Performs the hilbert transfor of an array of float32's.
	 *
	 * @param data the source array of the REAL numbers of which to take the
	 * Hilbert transform
	 *
	 * @param dest the destination array of REAL numbers for the results of the
	 * Hilbert transform
	 *
	 * @param size the number of elements in the data and dest arrays
	 */
	void hilbert(float32* data, float32* dest, uint32 size);

	/**
	 * Replaces the values of an array of cfloat32's with the array's inverse
	 * DFT. 
	 * 
	 * This code is based on code from
	 * http://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B.
	 *
	 * @param data the array whose values should be replaced with its inverse
	 * DFT
	 *
	 * @param size the number of elements in the data array
	 */
	void ifft(cfloat32* data, uint32 size);

	/**
	 * Produces an interleaved array of first an element from an original array
	 * of data and then an element from the original data's Hilbert transform.
	 * This function is intended to generate a two-channel output (I/Q output)
	 * for mixing applications.
	 *
	 * @param data the original data (left channel)
	 *
	 * @param dest the interleaved data (left channel original data, right
	 * channel transformed data) twice the size of the original data array
	 *
	 * @param size the number of elements in the data array (NOT in the
	 * destination array)
	 */
	void makeIQ(float32* data, float32* dest, uint32 size);

	void aconj(cfloat32* data, uint32 size) {
		for(int i = 0; i < size; i++) {
			data[i] = std::conj(data[i]);
		}
	}

	void fft(cfloat32* data, uint32 size) {
		// DFT
		uint32 k = size;
		uint32 n;
		float32 thetaT = M_PI / size;
		cfloat32 phiT(cos(thetaT), sin(thetaT));
		cfloat32 T;

		while(k > 1) {
			n = k;
			k >>= 1;
			phiT = phiT * phiT;
			T = 1.0L;

			for(uint32 l = 0; l < k; l++) {
				for(uint32 a = l; a < size; a += n) {
					uint32 b = a + k;
					cfloat32 t = data[a] -data[b];
					data[a] +=data[b];
					data[b] = t * T;
				}

				T *= phiT;
			}
		}

		// Decimate
		uint32 m = (uint32)log2(size);

		for(uint32 a = 0; a < size; a++) {
			uint32 b = a;

			// Reverse bits
			b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
			b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
			b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
			b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
			b = ((b >> 16) | (b << 16)) >> (32 - m);

			if (b > a)
			{
				cfloat32 t = data[a];
				data[a] =data[b];
				data[b] = t;
			}
		}
	}

	void hilbert(float32* data, float32* dest, uint32 size) {
		cfloat32 temp[size];

		for(int i = 0; i < size; i++) {
			temp[i] = data[i];
		}
		
		fft(temp, size);

		for(int i = size/2; i < size; i++) {
			temp[i] = 0;
		}

		ifft(temp, size);

		for(int i = 0; i < size; i++) {
			dest[i] = -2 * temp[i].imag();
		}
	}

	void ifft(cfloat32* data, uint32 size) {
		aconj(data, size);
		fft(data, size);
		aconj(data, size);

		for(int i = 0; i < size; i++) {
			data[i] /= size;
		}
	}

	void makeIQ(float32* data, float32* dest, uint32 size) {
		float32 quadData[size];
		hilbert(data, quadData, size);

		for(int i = 0; i < 2 * size; i += 2) {
			dest[i] = quadData[i/2];
			dest[i+1] = data[i/2];
		}
	}
}

#endif
