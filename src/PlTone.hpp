/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains the PlTone class.
 */

#ifndef PlTone_H
#define PlTone_H

#include "definitions.hpp"
#include "Sinusoid.hpp"

namespace radio {
	/**
	 * This class creates a PL tone (CTCSS tone) at a specified frequency
	 * in a baseband signal.
	 */
	class PlTone : Sinusoid {
		public:
			/**
			 * Creates a PlTone object.
			 *
			 * @param amplitude the amplitude (0-1) of the subcarrier. Assumes
			 * baseband signal has a peak-to-peak range of -1 to 1.
			 *
			 * @param data an array containing a portion of the discrete
			 * baseband signal
			 *
			 * @param size the number of elemeents in the data array
			 *
			 * @param frequency the frequency of the CTCSS tone in the baseband
			 * (not in the IF or RF signals)
			 *
			 * @param samplingRate the sampling frequency of the baseband
			 * signal
			 */
			PlTone(float32 amplitude, float32* data, uint32 size,
					float32 frequency, uint32 samplingRate = 48000);

			/**
			 * Adds the PL tone to the baseband signal.
			 */
			void Add();

		private:
			/**
			 * The amplitude of the subcarrier. Typically around 0.15 for CTCSS
			 * tones.
			 */
			float32 amplitude;

			/**
			 * The baseband signal to which to add the PL tone is added.
			 */
			float32* data;

			/**
			 * The number of elements in the data array
			 */
			uint32 size;
	};

	PlTone::PlTone(float32 amplitude, float32* data,
			uint32 size, float32 frequency, uint32 samplingRate)
		: Sinusoid(frequency, samplingRate) {
		this->data = data;
		this->amplitude = amplitude;
		this->size = size;

		for(uint32 i = 0; i < samplingRate; i++) {
			sinusoid[i] *= amplitude;
		}
	}

	void PlTone::Add() {
		for(uint32 i = 0; i < size; i++) {
			data[i] += amplitude * next();
			data[i] /= (1 + amplitude);  // ensures value <= 1
		}
	}
}

#endif
