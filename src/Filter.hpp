/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Defines the Filter class.
 */

#ifndef Filter_H
#define Filter_H

#include <cmath>
#include <vector>

#include "definitions.hpp"

namespace radio {
	/**
	 * This class implements a z-domain filter on a specified array of float32'''s
	 * (a.k.a. singles, floats). It requires the transfer function coefficients
	 * already be calculated (i.e., it does not generate the coefficients based
	 * on desired filter characteristics). MATLAB and its Signal Processing
	 * Toolbox can be used to generate the coefficients.
	 *
	 * While this class is designed to implement a single-section filter,
	 * several instances of the class can be created and run over the data array
	 * sequentially to effectively implement a multi-section filter.
	 *
	 * The class is designed (but not tested!) to allow for a z-domain transfer
	 * function with different orders of the zeros (numerator) and poles
	 * (denominator).
	 */
	class Filter {
		public:
			/**
			 * Initializes Filter based on a difference equation. 
			 *
			 * @param data array to be filtered. The filtered data will be
			 * placed here.
			 *
			 * @param size number of elements in the data array
			 *
			 * @param diffEq a vector containing two vectors of float32'''s
			 * (a.k.a. singles, floats), containing the numerator and
			 * denominator coefficients, respectively, of the z-domain tranfer
			 * function of the filter in decending order (z^0, z^-1, z^-2,
			 * etc.).
			 */
			Filter(float32* data, uint32 size,fparams& diffEq);

			/**
			 * Passes the data array through the digital filter and accounts for
			 * x[n] and y[n] values from the previous call to Pass().
			 */
			void Pass();

		protected:
			/**
			 * The order of the filter transfer function (i.e., the maximum of
			 * the orders of the numerator and denominator).
			 */
			uint8 eqLength;

			/**
			 * The number of elements in the data array.
			 */
			uint32 size;

			/**
			 * A pointer to the data array that should be filtered when Pass()
			 * is called.
			 */
			float32* data;

			/**
			 * A vector containing two vectors of float32'''s (a.k.a. singles,
			 * floats), containing the numerator and denominator coefficients,
			 * respectively, of the z-domain tranfer function of the filter
			 * in decending order (z^0, z^-1, z^-2, etc.).
			 */
			fparams diffEq;

			/**
			 * Vectors of the original (x[n]) and filtered (y[n]) values of the
			 * data array used to calculate the first filtered values of the
			 * data array. In spite of the type name, this variable does NOT
			 * contains filter parameters but rather the same data type that
			 * fparams represents.
			 */
			fparams prev;
	};

	Filter::Filter(float32* data, uint32 size, fparams& diffEq) {
		this->data = data;
		this->size = size;
		this->diffEq = diffEq;
		eqLength = std::max(this->diffEq[NUM].size(),
				this->diffEq[DEN].size());

		for(int i = 0; i < 2; i++) {
			prev.push_back(std::vector<float32>());
		}

		for(int i = 0; i < this->diffEq[NUM].size(); i++) {
			prev[OLD].push_back(0);
		}

		for(int i = 0; i < this->diffEq[DEN].size(); i++) {
			prev[NEW].push_back(0);
		}
	}

	void Filter::Pass() {
		float32 temp[size];

		// create first values in filtered data
		for(int i = 0; i< diffEq[NUM].size(); i++) {
			temp[i] = 0;

			for(int j = 0; j < prev[OLD].size(); j++) {
				temp[i] += diffEq[NUM][j] * (j > i 
						? prev[OLD][prev[OLD].size() - (j - i)] : data[i - j]);
			}

			for(int j = 1; j < prev[NEW].size(); j++) {
				temp[i] -= diffEq[DEN][j] * (j > i
						? prev[NEW][prev[NEW].size() - (j - i)] : temp[i - j]);
			}
		}

		// create the REST of the values in filtered data
		for(int i = eqLength; i < size; i++) {
			temp[i] = 0;

			for(int j = 0; j < diffEq[NUM].size(); j++) {
				temp[i] += diffEq[NUM][j] * data[i - j];
			}

			for(int j = 1; j < diffEq[NUM].size(); j++) {
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
