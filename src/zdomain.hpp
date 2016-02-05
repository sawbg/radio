#include <complex>

#include "definitions.hpp"

namespace lolz {

	/**
	 *
	 */
	void aconj(std::complex<float32>* data, uint32 size);

	/**
	 *
	 */
	void fft(std::complex<float32>* data, uint32 size);

	/**
	 *
	 */
	void hilbert(float32* data, float32* dest, uint32 size);

	/**
	 *
	 */
	void ifft(std::complex<float32>* data, uint32 size);

	void aconj(std::complex<float32>* data, uint32 size) {
		for(int i = 0; i < size; i++) {
			data[i] = std::conj(data[i]);
		}
	}

	void fft(std::complex<float32>* data, uint32 size) {
		// DFT
		uint32 k = size;
		uint32 n;
		float32 thetaT = M_PI / size;
		std::complex<float32> phiT(cos(thetaT), sin(thetaT));
		std::complex<float32> T;

		while(k > 1) {
			n = k;
			k >>= 1;
			phiT = phiT * phiT;
			T = 1.0L;

			for(uint32 l = 0; l < k; l++) {
				for(uint32 a = l; a < size; a += n) {
					uint32 b = a + k;
					std::complex<float32> t = data[a] -data[b];
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
				std::complex<float32> t = data[a];
				data[a] =data[b];
				data[b] = t;
			}
		}
	}

	void hilbert(float32* data, float32* dest, uint32 size) {
		std::complex<float32> temp[size];

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

	void ifft(std::complex<float32>* data, uint32 size) {
		aconj(data, size);
		fft(data, size);
		aconj(data, size);

		for(int i = 0; i < size; i++) {
			data[i] /= size;
		}
	}
}
