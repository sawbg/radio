/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains the classes for the various types of modulation supported by
 * the program.
 */

#ifndef modulation_H
#define modulation_H

#include <array>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "definitions.hpp"

namespace radio {

	/**
	 * This class, while not intended to be called directly, is a superclass for
	 * the classes of the modulation forms used in this project.
	 */
	class Modulator {
		public:
			/**
			 * Requires subclasses to implement a Mod() function.
			 */
			virtual void Mod() = 0;

		protected:
			/**
			 * An array of sinusoid values of the carrier wave
			 */
			float32* carrier;

			/**
			 * The index tracking the value of the carrier sinusoid (held in
			 * carrier) to be used in the next calculation
			 */
			uint32 carrInd = 0;

			/**
			 * The data to modulate (i.e., baseband signal), which is then
			 * replaced by its modulated signal of the same sampling rate
			 */
			float32* data;

			/**
			 * The sampling rate of the baseband and generated IF signals
			 */
			float32 rate;

			/**
			 * The number of elements in the data array
			 */
			uint32 size;

			/**
			 * Creates a Modulator with a default carrier intermediate frequency
			 * and default sampling rate. Intended to be called only by
			 * subclasses.
			 *
			 * @param data the data array initially containing the baseband
			 * signal
			 *
			 * @param size the number of elements in the data array
			 */
			Modulator(float32 data[], uint32 size)
				: Modulator(20000, 48000, data, size) {};

			/**
			 * Creates a Modulator with the specified parameters. Intended to be
			 * called only by subclasses.
			 *
			 * @param freqInter the frequency of the IF carrier sinusoid
			 *
			 * @param rate the sampling rate of the baseband and IF signals
			 *
			 * @param data the array holding initially the baseband signal
			 *
			 * @param size the number of elements in data
			 */
			Modulator(float32 freqInter, uint32 rate,
					float32 data[], uint32 size);

		private:
			/**
			 * The frequency of the IF carrier sinusoid
			 */
			float32 freqCarrier;

			/**
			 * Generates the IF carrier sinusoid based on the frequency
			 * specified by freqCarrier.
			 */
			void makeCarrier();
	};

	class DsbLcModulator : Modulator {
		public:
			/**
			 * Creates a double-sideband, large-carrier (i.e., broadcast AM
			 * modulation) Modulator with the default intermediate frequency and
			 * sampling rate.
			 *
			 * @param data the data array initially containing the baseband
			 * signal
			 *
			 * @param size the number of elements in the data array
			 */
			DsbLcModulator(float32 data[], uint32 size)
				: Modulator(data,size) {};

			/**
			 * Creates a double-sideband, large-carrier (i.e., broadcast AM
			 * modulation) Modulator with the given parameters.
			 *
			 * @param freqInter the frequency of the IF carrier sinusoid
			 *
			 * @param rate the sampling rate of the baseband and IF signals
			 *
			 * @param data the array holding initially the baseband signal
			 *
			 * @param size the number of elements in data
			 */
			DsbLcModulator(uint8 freqInter, uint32 rate,
					float32 data[], uint32 size)
				: Modulator(freqInter, rate, data, size) {};

			/**
			 * Modulates the data using double-sideband, large-carrier
			 * modulation.
			 */
			void Mod();
	};

	class DsbScModulator : Modulator {
		public:
			/**
			 * Creates a double-sideband, large-carrier (i.e., broadcast AM
			 * modulation) Modulator with the default intermediate frequency and
			 * sampling rate.
			 *
			 * @param data the data array initially containing the baseband
			 * signal
			 *
			 * @param size the number of elements in the data array
			 */
			DsbScModulator(float32 data[], uint32 size)
				: Modulator(data,size) {};

			/**
			 * Creates a double-sideband, supressed-carrier Modulator with the
			 * given parameters.
			 *
			 * @param freqInter the frequency of the IF carrier sinusoid
			 *
			 * @param rate the sampling rate of the baseband and IF signals
			 *
			 * @param data the array holding initially the baseband signal
			 *
			 * @param size the number of elements in data
			 */
			DsbScModulator(uint8 freqInter, uint32 rate,
					float32 data[], uint32 size)
				: Modulator(freqInter, rate, data, size) {};

			/**
			 * Modulates the data using double-sideband, supressed-carrier
			 * modulation.
			 */
			void Mod();
	};

	Modulator::Modulator(float32 carrier,
			uint32 rate, float32 data[],
			uint32 size) {
		freqCarrier = carrier;
		this->rate = rate;
		this->data = data;
		this->size = size;
		this->carrier = (float32*)malloc(rate*sizeof(float32));
		makeCarrier();
	}

	void Modulator::makeCarrier() {
		for(int i = 0; i < rate; i++) {
			carrier[i] = cos(2 * M_PI * freqCarrier
					* i / rate);
		}
	}

	void DsbLcModulator::Mod() {
		for(int i = 0; i < size; i++, carrInd++) {
			if(carrInd >= rate) carrInd = 0;
			data[i] = ((data[i] + 1) * carrier[carrInd]) / 2;
		}
	}

	void DsbScModulator::Mod() {
		float32 temp;

		for(int i = 0; i < size; i++,
				carrInd = (carrInd < rate ? carrInd + 1 : 0)) {
			temp = ((float)data[i]/128) - 1;
			data[i] = temp * carrier[carrInd];
		}
	}
}

#endif
