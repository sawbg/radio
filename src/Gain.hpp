#ifndef Gain_H
#define Gain_H

#include <cmath>

#include "definitions.hpp"

namespace radio {
	/**
	 * Applies a gain to a (baseband) signal.
	 */
	class Gain {
		public:
			/**
			 * Initializes a Gain object and converts gain from decibels to a
			 * standard value.
			 *
			 * @param data the signal to which the gain is applied
			 *
			 * @param size the number of elements in the data array
			 *
			 * @param gaindB the desired gain in decibels (of power)
			 */
			Gain(float32* data, uint32 size, float32 gaindB);

			/**
			 * Applies the gain to the signal contained in the data array
			 */
			void Apply();

		private:
			/**
			 * A pointer to the discrete signal to which the gain is applied
			 */
			float32* data;

			/**
			 * The non-logrithmic gain
			 */
			float32 gainCoeff;

			/**
			 * Whether the gain has resulted in a gain outside of the range -1 <
			 * x[n] < 1
			 */
			bool hasClipped = false;

			/**
			 * The number of elements in the data array
			 */
			uint32 size;

	};

	Gain::Gain(float32* data, uint32 size, float32 gaindB) {
		this->data = data;
		this->size = size;
		gainCoeff = pow(10, gaindB / 20);
	}

	void Gain::Apply() {
		for(uint32 i = 0; i < size; i++) {
			data[i] *= gainCoeff;

			if((data[i] > 1 || data[i] < -1) && !hasClipped) {
				hasClipped = true;
				std::cerr << "Baseband clipping has occurred!"
					<< std::endl;
			}
		}
	}
}

#endif
