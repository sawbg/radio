/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains the Subcarrier class
 */

#ifndef Subcarrier_H
#define Subcarrier_H

#include "definitions.hpp"
#include "Sinusoid.hpp"

namespace radio {
	/**
	 * This class creates a CTCSS subcarrier (PL tone) at a specified frequency
	 * in a baseband signal.
	 */
	class Subcarrier : Sinusoid {
		public:
			/**
			 * Creates a Subcarrier object.
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
			Subcarrier(float32 amplitude, float32* data, uint32 size,
					float32 frequency, uint32 samplingRate);

			/**
			 * Adds the CTCSS tone to the baseband signal.
			 */
			Add();

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
	}

	Subcarrier::Subcarrier(float32* data, float32 amplitude,
			float32 frequency, uint32 samplingRate)
		: Sinusoid(frequency, samplingRate){
		this->data = data;
		this->amplitude = amplitude;
		this->size = size;

		for(uint32 i = 0; i < samplingRate; i++) {
			sinusoid[i] *= amplitude;
		}
	}

	Subcarrier::Add() {
		for(uint32 i = 0; i < size; i++) {
			data[i] += next();
		}
	}
}

#endif
