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
/**
 * This class creates an easy-to-call sinusoid that will preserve its phase
 * throughout its lifespan. Essentially, it is a ring buffer.
 */
	class Sinusoid {
		public:
			/**
			 * Creates a ring-buffer sinusoid.
			 */
			Sinusoid(float32 frequency, uint32 samplingRate);

			/**
			 * Free arrays malloc'd in the constructor.
			 */
			~Sinusoid();

			/**
			 * Provides the next value of the sinusoid in a manner consistant
			 * with a ring buffer.
			 */
			float32 next();

			/**
			 * Provides the next value of the sinusoid shifted 90 degrees in a
			 * manner consistant with a ring buffer.
			 */
			float32 nextShifted();

		protected:
			/**
			 * The frequency of the sinusoid
			 */
			float32 frequency;

			/**
			 * The current index of the sinusoid's arrays
			 */
			uint32 carrierIndex = 0;

			/**
			 * The sampling rate
			 */
			uint32 samplingRate;

			/**
			 * Initialized as an array of the sinusoid values
			 */
			float32* sinusoid;

			/**
			 * Initialized as an array of the sinusoid values shifted 90
			 * degrees
			 */
			float32* sinusoidShift90;
	};

	Sinusoid::Sinusoid(uint32 frequency, uint32 samplingRate) {
		this->frequency = carrierFreq;
		this->samplingRate = samplingRate;
		sinusoid = (float32*)std::malloc(samplingRate * sizeof(float32));
		sinusoidShift90 = (float32*)std::malloc(samplingRate * sizeof(float32));

		float32 arg = 2 * M_PI * frequency / samplingRate;

		for(uint32 i; i < samplingRate; i++) {
			// cosine argument evaluates as float due to M_PI and frequency
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
