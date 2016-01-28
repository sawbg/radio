#ifndef modulation_H
#define modulation_H

#include <cmath>

#include "definitions.hpp"

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
		float* data;

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
		Modulator(float* data, uint16 size)
			: Modulator(2000, 48000, data, size) {};

		/**
		 *
		 */
		Modulator(float32 freqInter, uint32 rate,
				float* data,  uint16 size);

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
		DsbLcModulator(float* data, uint16 size)
			: Modulator(data,size) {};

		/**
		 *
		 */
		DsbLcModulator(float32 freqInter, uint32 rate,
				float* data, uint16 size)
			: Modulator(freqInter, rate, data, size) {};

		/**
		 *
		 */
		void Mod();
};

Modulator::Modulator(float32 carrier, uint32 rate, float* data, uint16 size) {
	freqCarrier = carrier;
	this->rate = rate;
	this->data = data;
	this->size = size;
	makeCarrier();
}

void Modulator::makeCarrier() {
	for(int i = 0; i < rate; i++) {
		carrier[i] = sin(2 * M_PI * freqCarrier * (float)i / rate);
	}
}

void DsbLcModulator::Mod() {
	for(int i = 0; i < size;
			i++, carrInd = (carrInd < rate ? carrInd + 1 : 0)) {
		char hey = *((char*)&data[i]);
		data[i] = (data[i] + 1) * carrier[carrInd];
	}
}


#endif
