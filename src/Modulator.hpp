/**
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
#include "Filter.hpp"
#include "fvectors.hpp"
#include "Sinusoid.hpp"
#include "zdomain.hpp"

namespace radio {

	/**
	 * The default intermediate carrier frequency
	 */
	const uint32 FREQ_INTERMEDIATE = 20000;

	/**
	 * The default sampling rate (frequency)
	 */
	const uint32 SAMPLING_RATE = 48000;

	/**
	 * This class, while not intended to be called directly, is a superclass for
	 * the classes of the modulation forms used in this project.
	 */
	class Modulator {
		public:
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
			 *
			 * @param type form of modulation to use
			 */
			Modulator(float32 data[], uint32 size, ModulationType type,
					float32 freqInter = FREQ_INTERMEDIATE,
					uint32 rate = SAMPLING_RATE);

			/**
			 *
			 */
			~Modulator();

			/**
			 * Modulates the audio currently in the data array.
			 */
			void Mod();

		private:
			/**
			 * The data to modulate (i.e., baseband signal), which is then
			 * replaced by its modulated signal of the same sampling rate
			 */
			float32* data;

			/**
			 * The frequency of the IF carrier sinusoid
			 */
			float32 freqCarrier;


			/**
			 * THe Hilbert transform of the signal in the data array
			 */
			float32* hilData = nullptr;

			/**
			 * The sampling rate of the baseband and generated IF signals
			 */
			float32 rate;

			/**
			 * The number of elements in the data array
			 */
			uint32 size;

			/**
			 * The type of modulation to implement
			 */
			ModulationType type;
	};

	Modulator::Modulator(float32 data[], uint32 size, ModulationType type,
			float32 freqInter, uint32 rate) {
		freqCarrier = freqInter;
		this->rate = rate;
		this->data = data;
		this->size = size;
		this->type = type;

		if(type == ModulationType::USB_HILBERT
				|| type == ModulationType::LSB_HILBERT) {
			hilData = (float32*)malloc(size*sizeof(float32));
		}
	}

	Modulator::~Modulator() {
		if(hilData != nullptr) free(hilData);
	}

	void Modulator::Mod() {
		// these variables should only ever be created once
		static float32 fmArg = 2 * M_PI * freqCarrier / (float32)rate;
		static float32 fmK = 2 * M_PI / rate;
		static float32 fmSum = 0;  // cummulative sum used in FM modulation
		static Filter lsbFilter(data, size, F_LOWERSIDEBAND);
		static Sinusoid sinusoid(freqCarrier, rate);  // IF carrier sinusoid
		static Filter usbFilter(data, size, F_UPPERSIDEBAND);

		// take hilbert transform if necessary
		if(type == ModulationType::USB_HILBERT
				|| type == ModulationType::LSB_HILBERT) {
			hilbert(data, hilData, size);
		} else if(type == ModulationType::FM_NARROW) {
			fmK *= 2.5;
		} else if(type == ModulationType::FM_WIDE) {
			fmK *= 5;
		}

		// perform main modulation
		for(uint32 i = 0; i < size; i++) {
			switch(type) {
				case ModulationType::DSB_LC:
					data[i] = ((data[i] + 1) * sinusoid.next()) / 2;
					break;

				case ModulationType::DSB_SC:
				case ModulationType::USB_FILTERED:
				case ModulationType::LSB_FILTERED:
					data[i] = data[i] * sinusoid.next();
					break;

				case ModulationType::USB_HILBERT:
					data[i] = data[i] * sinusoid.next()
						- hilData[i] * sinusoid.nextShifted();
					break;

				case ModulationType::LSB_HILBERT:
					data[i] = data[i] * sinusoid.next()
						+ hilData[i] * sinusoid.nextShifted();
					break;

				case ModulationType::FM_NARROW:
				case ModulationType::FM_WIDE:
					fmSum += fmK * data[i];
					data[i] = cos(fmArg * i + fmSum);
					break;
			}
		}

		// filter out a sideband if using filtered SSB modulation
		if(type == ModulationType::LSB_FILTERED) {
			lsbFilter.Pass();
		} else if(type == ModulationType::USB_FILTERED) {
			usbFilter.Pass();
		}
	}
}

#endif
