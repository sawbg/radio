#ifndef modulation_H
#define modulation_H

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
			std::vector<float> carrier;

			/**
			 *
			 */
			uint32 carrInd = 0;

			/**
			 *
			 */
			uint8* data;

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
			Modulator(uint8 data[], uint16 size)
				: Modulator(2000, 48000, data, size) {};

			/**
			 *
			 */
			Modulator(float32 freqInter, uint32 rate,
					uint8 data[], uint16 size);

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
			DsbLcModulator(uint8 data[], uint16 size)
				: Modulator(data,size) {};

			/**
			 *
			 */
			DsbLcModulator(uint8 freqInter, uint32 rate,
					uint8 data[], uint16 size)
				: Modulator(freqInter, rate, data, size) {};

			/**
			 *
			 */
			//	void Mod();
	};

	class DsbScModulator : Modulator {
		public:
			/*
			 *
			 */
			DsbScModulator(uint8 data[], uint16 size)
				: Modulator(data,size) {};

			/**
			 *
			 */
			DsbScModulator(uint8 freqInter, uint32 rate,
					uint8 data[], uint16 size)
				: Modulator(freqInter, rate, data, size) {};
	};

	Modulator::Modulator(float32 carrier,
			uint32 rate, uint8 data[],
			uint16 size) {
		freqCarrier = carrier;
		this->rate = rate;
		this->data = data;
		this->size = size;
		makeCarrier();
	}

	void Modulator::makeCarrier() {
		for(int i = 0; i < rate; i++) {
			carrier.push_back(sin(2 * M_PI * freqCarrier
						* (float)i / rate));
		}
	}

	void DsbLcModulator::Mod() {
		float temp;

		for(int i = 0; i < size; i++,
				carrInd = (carrInd < rate ? carrInd + 1 : 0)) {

			/*
			 * Normally, 1 would be subtracted from temp in the
			 * uint8 to float conversion, but we'd also add one for
			 * DSB-LC modulation, so it cancels out.
			 */
			temp = ((float)data[i]/128);
			data[i] = (temp * carrier[carrInd] + 1) * 128;
		}
	}

	void DsbScModulator::Mod() {
		float temp;

		for(int i = 0; i < size; i++,
				carrInd = (carrInd < rate ? carrInd + 1 : 0)) {
			temp = ((float)data[i]/128) - 1;
			data[i] = (temp * carrier[carrInd] + 1) * 128;
		}
	}
}

#endif
