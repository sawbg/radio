#ifndef Filter_H
#define Filter_H

#include <cmath>
#include <vector>

#include "definitions.hpp"

namespace lolz {
	/**
	 *
	 */
	class Filter {
		public:
			/**
			 *
			 */
			Filter(float32* data, uint32 size,
					std::vector<std::vector<float32>>& diffEq);

			/**
			 *
			 */
			void Pass();

		protected:
			/**
			 *
			 */
			uint8 eqLength;

			/**
			 *
			 */
			uint32 size;

			/**
			 *
			 */
			float32* data;

			/**
			 *
			 */
			std::vector<std::vector<float32>> diffEq;

			/**
			 *
			 */
			std::vector<std::vector<float32>> prev;
	};

	Filter::Filter(float32* data, uint32 size,
			std::vector<std::vector<float32>>& diffEq) {
		this->data = data;
		this->size = size;
		this->diffEq = diffEq;
		eqLength = std::max(this->diffEq[NUM].size(),
				this->diffEq[DEN].size());

		for(int i = 0; i < this->diffEq[NUM].size(); i++) {
			prev[NUM].push_back(0);
		}

		for(int i = 0; i < this->diffEq[DEN].size(); i++) {
			prev[DEN].push_back(0);
		}
	}

	void Filter::Pass() {
		float32 temp[size];

		// create first values in filtered data
		for(int i = 0; i< diffEq[NUM].size(); i++) {
			temp[i] = 0;

			for(int j = 0; j < prev[OLD].size(); j++) {
				temp[i] += diffEq[NUM][j] * (j > i 
						? prev[OLD][prev[OLD].size() - (j - i)] : data[j - i]);
			}

			for(int j = 0; j < prev[NEW].size(); j++) {
				temp[i] -= diffEq[DEN][j] * (j > i
						? prev[NEW][prev[NEW].size() - (j - i)] : temp[j - i]);
			}
		}

		// create the REST of the values in filtered data
		for(int i = 0; i < size; i++) {
			temp[i] = 0;

			for(int j = 0; j < diffEq[NUM].size(); j++) {
				temp[i] += diffEq[NUM][j] * data[i - j];
			}

			for(int j = 0; j < diffEq[NUM].size(); j++) {
				temp[i] -= diffEq[DEN][j] * temp[i - j];
			}
		}

		// save final values of data and filtered data
		for(int i = size - diffEq[NUM].size(), j = 0; i < size; i++, j++) {
			prev[OLD][j] = data[i];
		}

		for(int i = size - diffEq[DEN].size(), j = 0; i < size; i++, j++) {
			prev[NEW][j] = temp[i];
		}

		// transfer filtered data to original data's buffer
		for(int i = 0; i < size; i++) {
			data[i] = temp[i];
		}
	}
}

#endif
