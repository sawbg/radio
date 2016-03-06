/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Defines the transfer function coefficients used in the instances of
 * the Filter class in this program.
 */

#ifndef fvectors_H
#define fvectors_H

#include <vector>

#include "definitions.hpp"

namespace radio {
	/**
	 * Baseband filter coefficients.
	 */
	fparams F_BASEBAND = { std::vector<float32> {
		0.0008977019461,
			-0.002215694636,
			0.001372192986,
			0.001372192986,
			-0.002215694636,
			0.0008977019461
	}, std::vector<float32> {
		1,
			-4.678616047,
			8.822912216,
			-8.379911423,
			4.007629871,
			-0.7719064355
	} };

	/**
	 * Lower-sideband filter coefficients.
	 */
	fparams F_LOWERSIDEBAND = { std::vector<float32> {
		0.0008977019461,
			-0.002215694636,
			0.001372192986,
			0.001372192986,
			-0.002215694636,
			0.0008977019461
	}, std::vector<float32> {
		1,
			-4.678616047,
			8.822912216,
			-8.379911423,
			4.007629871,
			-0.7719064355
	} };

	/**
	 * Upper-sideband filter coefficients.
	 */
	fparams F_UPPERSIDEBAND = { std::vector<float32> {
		0.0008977019461,
			-0.002215694636,
			0.001372192986,
			0.001372192986,
			-0.002215694636,
			0.0008977019461
	}, std::vector<float32> {
		1,
			-4.678616047,
			8.822912216,
			-8.379911423,
			4.007629871,
			-0.7719064355
	} };


}

#endif
