/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains the Sinusoid class.
 */

#ifndef Sinusoid_H
#define Sinusoid_H

#include <cmath>
#include <cstdlib>

#include "definitions.hpp"

namespace radio {
/**
 * This class creates an easy-to-call pair of sinusoids, pi/2 radians out of
 * phase with each other, that will preserve its phase throughout its
 * lifespan. Essentially, it is a ring buffer.
 */
	class Sinusoid {
		public:
			/**
			 * Creates two ring-buffer sinusoids.
			 */
			Sinusoid(float32 frequency, uint32 samplingRate = 48000);

			/**
			 * Frees arrays malloc'ed in the constructor.
			 */
			~Sinusoid();

			/**
			 * Provides the next value of the sinusoid in a manner consistant
			 * with a ring buffer.
			 */
			float32 next();

			/**
			 * Provides the next value of the shifted sinusoid in a
			 * manner consistant with a ring buffer.
			 */
			float32 nextShifted();

		protected:
			/**
			 * The frequency of the sinusoid.
			 */
			float32 frequency;

			/**
			 * The current index of the sinusoid's unshifted array.
			 */
			uint32 sinIndex = 0;

			/**
			 * The current index of the shifted sinusoid's array.
			 */
			uint32 sinIndexShifted = 0;
		
			/**
			 * The sampling rate.
			 */
			uint32 samplingRate;

			/**
			 * Initialized as an array of the sinusoid values.
			 */
			float32* sinusoid;

			/**
			 * Initialized as an array of the sinusoid values shifted 90
			 * degrees.
			 */
			float32* sinusoidShift90;
	};

	Sinusoid::Sinusoid(float32 frequency, uint32 samplingRate) {
		this->frequency = frequency;
		this->samplingRate = samplingRate;
		sinusoid = (float32*)std::malloc(samplingRate * sizeof(float32));
		sinusoidShift90 = (float32*)std::malloc(samplingRate * sizeof(float32));

		float32 arg = 2 * M_PI * frequency / samplingRate;

		for(uint32 i = 0; i < samplingRate; i++) {
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
		if(sinIndex >= samplingRate) sinIndex = 0;
		return sinusoid[sinIndex++];
	}

	float32 Sinusoid::nextShifted() {
		if(sinIndexShifted >= samplingRate) sinIndexShifted = 0;
		return sinusoidShift90[sinIndexShifted++];
	}
}

#endif
