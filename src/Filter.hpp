/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Defines the Filter class.
 * @bug Discontinuities created at the beginning of each pass
 */

#ifndef Filter_H
#define Filter_H

#include <cmath>
#include <vector>

#include "definitions.hpp"

namespace radio {
	/**
	 * This class implements a z-domain filter on a specified array of
	 * float32's (a.k.a. singles, floats). It requires the transfer function
	 * coefficients be already calculated (i.e., it does not generate the
	 * coefficients based on desired filter characteristics). MATLAB and its
	 * Signal Processing Toolbox can be used to generate the coefficients.
	 *
	 * While this class is designed to implement a single-section filter,
	 * several instances of the class can be created and run over the data array
	 * in sequence to effectively implement a multi-section filter.
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
			 * @param diffEq a vector containing two vectors of float32's
			 * (a.k.a. singles, floats), that contains the numerator and
			 * denominator coefficients, respectively, of the z-domain tranfer
			 * function of the filter in decending order (z^0, z^-1, z^-2,
			 * etc.).
			 */
			Filter(float32* data, uint32 size, fparams& diffEq);

			/**
			 * Passes the data array through the digital filter but does not
			 * account for previous x[n] and y[n] values from the previous call
			 * to Pass().
			 */
			void Pass();

		protected:
			/**
			 * The number of terms in the numerator (or denomenator) of the
			 * transfer function (i.e., function order + 1).
			 */
			uint8 eqLength;

			/**
			 * The number of elements in the data array.
			 */
			uint32 size;

			/**
			 * A pointer to the start of the data array to be filtered when
			 * Pass() is called.
			 */
			float32* data;

			/**
			 * A vector containing two vectors of float32's (a.k.a. singles,
			 * floats), containing the numerator and denominator coefficients,
			 * respectively, of the z-domain tranfer function of the filter
			 * in decending order (z^0, z^-1, z^-2, etc.).
			 */
			fparams diffEq;
	};

	Filter::Filter(float32* data, uint32 size, fparams& diffEq) {
		this->data = data;
		this->size = size;
		this->diffEq = diffEq;
		eqLength = this->diffEq[DEN].size();
	}

	void Filter::Pass() {
		float64 temp[size];

		// create first values in filtered data
		for(int i = 0; i< eqLength; i++) {
			temp[i] = 0;

			for(int j = 0; j < eqLength; j++) {
				temp[i] += diffEq[NUM][j] * (j > i ? 0 : data[i - j]);
			}

			for(int j = 1; j < eqLength; j++) {
				temp[i] -= diffEq[DEN][j] * (j > i ? 0 : temp[i - j]);
			}
		}

		// create the REST of the values in filtered data
		for(int i = eqLength; i < size; i++) {
			temp[i] = 0;

			for(int j = 0; j < eqLength; j++) {
				temp[i] += diffEq[NUM][j] * data[i - j];
			}

			for(int j = 1; j < eqLength; j++) {
				temp[i] -= diffEq[DEN][j] * temp[i - j];
			}
		}

		// save final values of data and filtered data
	for(int i = 0; i < size; i++) {
			data[i] = temp[i];
		}
	}
}

#endif
