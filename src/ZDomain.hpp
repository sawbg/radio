#ifndef ZDomain_H
#define ZDomain_H

#include <cmath>
#include <cstring>
#include <complex>
#include <functional>

#include "definitions.hpp"

namespace lolz {
	/**
	 *
	 */
	class ZDomain {
		public:

			/**
			 *
			 */
			uint16 size;

			/**
			 *
			 */
			float32* orig;

			/**
			 *
			 */
			std::complex<float32>* temp;

			/**
			 *
			 */
			ZDomain(float32* orig, float32* dest, uint16 size);

			/**
			 *
			 */
			~ZDomain();

			/**
			 *
			 */
			void fft();

			/**
			 *
			 */
			void hilbert();

			/**
			 *
			 */
			void ifft();

		protected:
			/**
			 *
			 */
			void _fft();

			/**
			 *
			 */
			void _ifft();
	};

	ZDomain::ZDomain(float32* orig, uint16 size) {
		this->orig = orig;
		this->size = size;
		temp = (std::complex<float32>*)malloc(size
				* sizeof(std::complex<float32>*));
		
		for(uint32 i = 0; i < size; i++) {
			temp[i] = std::complex<float32>(orig[i], 0);
		}
	}

	ZDomain::~ZDomain() {
		free(temp);
	}

	void ZDomain::_fft() {
		// DFT
		uint32 k = size;
		uint32 n;
		float32 thetaT = M_PI / N;
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
					std::complex<float32> t = temp[a] - temp[b];
					temp[a] += temp[b];
					temp[b] = t * T;
				}

				T *= phiT;
			}
		}

		// Decimate
		uint32 m = (uint32)log2(size);

		for(uint16 a = 0; a < size; a++) {
			uint16 b = a;

			// Reverse bits
			b = (((b & 0xaaaa) >> 1) | ((b & 0x5555) << 1));
			b = (((b & 0xcccc) >> 2) | ((b & 0x3333) << 2));
			b = (((b & 0xf0f0) >> 4) | ((b & 0x0f0f) << 4));
			b = (((b & 0xff00) >> 8) | ((b & 0x00ff) << 8));
			b = ((b >> 8) | (b << 8)) >> (16 - m);

			if (b > a)
			{
				std::complex<float32> t = temp[a];
				temp[a] = temp[b];
				temp[b] = t;
			}
		}
	}

	void ZDomain::_ifft() {

	}

	/*void ZDomain::fft(std::complex<float32> dest) {
		
	}*/

	void ZDomain::hilbert() {

	}

	/*void ZDomain::ifft {

	}*/

}

#endif