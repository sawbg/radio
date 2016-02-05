#ifndef modulation_H
#define modulation_H

#include <array>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "definitions.hpp"

namespace lolz {

	/**
	 *
	 */
	class Modulator {
		public:
			/**
			 *
			 */
			virtual void Mod() = 0;

		protected:
			/**
			 *
			 */
			float32* carrier;

			/**
			 *
			 */
			uint32 carrInd = 0;

			/**
			 *
			 */
			float32* data;

			/**
			 *
			 */
			float32 rate;

			/**
			 *
			 */
			uint16 size;

			/**
			 *
			 */
			Modulator(float32 data[], uint16 size)
				: Modulator(20000, 48000, data, size) {};

			/**
			 *
			 */
			Modulator(float32 freqInter, uint32 rate,
					float32 data[], uint16 size);

		private:
			/**
			 *
			 */
			float32 freqCarrier;

			/**
			 *
			 */
			void makeCarrier();
	};

	class DsbLcModulator : Modulator {
		public:
			/**
			 *
			 */
			DsbLcModulator(float32 data[], uint16 size)
				: Modulator(data,size) {};

			/**
			 *
			 */
			DsbLcModulator(uint8 freqInter, uint32 rate,
					float32 data[], uint16 size)
				: Modulator(freqInter, rate, data, size) {};

			/**
			 *
			 */
			void Mod();
	};

	class DsbScModulator : Modulator {
		public:
			/*
			 *
			 */
			DsbScModulator(float32 data[], uint16 size)
				: Modulator(data,size) {};

			/**
			 *
			 */
			DsbScModulator(uint8 freqInter, uint32 rate,
					float32 data[], uint16 size)
				: Modulator(freqInter, rate, data, size) {};

			/**
			 *
			 */
			void Mod();
	};

	Modulator::Modulator(float32 carrier,
			uint32 rate, float32 data[],
			uint16 size) {
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
