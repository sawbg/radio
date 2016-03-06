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

namespace radio {

	/**
	 *
	 */
	const uint32 FREQ_IF = 20000;

	/**
	 *
	 */
	const uint32 SAMPLING_RATE = 48000;

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
			 *
			 */
			Sinusoid sinusoid;

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
			Modulator(float32 data[], uint32 size, float32 freqInteri = FREQ_IF,
					uint32 rate = SAMPLING_RATE);

		private:
			/**
			 * The frequency of the IF carrier sinusoid
			 */
			float32 freqCarrier;
	};

	class DsbLcModulator : Modulator {
		public:
			using Modulator::Modulator;
			void Mod();
	};

	class DsbScModulator : Modulator {
		public:
			using Modulator::Modulator; 
			void Mod();
	};

/**
 *
 */
	class SsbModulator : Modulator {
		protected:
			/**
			 * Creates a single-sideband, supressed-carrier Modulator with the
			 * default intermediate frequency and sampling rate. This form of
			 * single-sideband modulation generates a DSB-SC signal and
			 * filtering out the unwanted sideband.
			 *
			 * @param freqInter the frequency of the IF carrier sinusoid
			 *
			 * @param rate the sampling rate of the baseband and IF signals
			 *
			 * @param data the array holding initially the baseband signal
			 *
			 * @param size the number of elements in data
			 *
			 * @param sideband to allow in signal
			 */
			SsbModulator(float32 data[], uint32 size, Sideband sideband,
					uint32 freqInter = FREQ_IF, uint32 rate = SAMPLING_RATE)
				: Modulator(freqInter, rate, data, size);

		private:
			Sideband sideband;
	};

	/**
	 * 
	 */
	class FilteredSsbModulator : SsbModulator {
		public:
			using SsbModulator::SsbModulator;
			void Mod();
	}

	/**
	 *
	 */
	class HilbertSsbModulator : SsbModulator {
		public:
			using SsbModulator::SsbModulator;
			void Mod();
	}

	Modulator::Modulator(float32 carrier,
			uint32 rate, float32 data[],
			uint32 size) {
		freqCarrier = carrier;
		this->rate = rate;
		this->data = data;
		this->size = size;
		sinusoid = Sinusoid(carrier, rate);
	}

	SsbModulator::SsbModulator(float32 data[], uint32 size, Sideband sideband,
			uint32 freqInter, uint32 rate) {
		this->sideband = sideband;
	}

	FilteredSsbModulator(

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
	
	FilteredSsbModulator::Mod() {	
		
	}

	HilbertSsbModulator() {
		
	}
}

#endif
