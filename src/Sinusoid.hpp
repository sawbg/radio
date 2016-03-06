/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains the Sinusoid class
 */

#ifndef Sinusoid_H
#define Sinusoid_H

#include <cmath>
#include <cstdlib>

#include "definitions.hpp"

namespace radio {
	class Sinusoid {
		public:
			/**
			 *
			 */
			Sinusoid(float32 carrierFreq, uint32 samplingRate);

			/**
			 *
			 */
			~Sinusoid();

			/**
			 *
			 */
			float32 next();

			/**
			 *
			 */
			float32 nextShifted();

		private:
			/**
			 *
			 */
			float32 carrierFreq;

			/**
			 *
			 */
			uint32 carrierIndex = 0;

			/**
			 *
			 */
			uint32 samplingRate;

			/**
			 *
			 */
			float32* sinusoid;

			/**
			 *
			 */
			float32* sinusoidShift90;
	};

	Sinusoid::Sinusoid(uint32 carrierFreq, uint32 samplingRate) {
		this->carrierFreq = carrierFreq;
		this->samplingRate = samplingRate;
		sinusoid = (float32*)std::malloc(samplingRate * sizeof(float32));
		sinusoidShift90 = (float32*)std::malloc(samplingRate * sizeof(float32));

		float32 arg = 2 * M_PI * carrierFreq / samplingRate;

		for(uint32 i; i < samplingRate; i++) {
			// cosine argument evaluates as float due to M_PI and carrierFreq
			sinusoid[i] = cos(arg * i);
			sinusoidShift90[i] = sin(arg * i);
		}
	}

	Sinusoid::~Sinusoid() {
		free(sinusoid);
		free(sinusoidShift90);
	}

	float32 Sinusoid::next() {
		if(carrierIndex >= samplingRate) carrierIndex = 0;
		return sinusoid[carrierIndex++];
	}

	float32 Sinusoid::nextShifted() {
		if(carrierIndex >= samplingRate) carrierIndex = 0;
		return sinusoidShift90[carrierIndex++];
	}
}

#endif
