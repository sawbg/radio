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
	 * Baseband filter coefficients. Generated with MATLAB 2015A.
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
	 * Lower-sideband filter coefficients. Generated with MATLAB 2015A.
	 */
	fparams F_LOWERSIDEBAND = { std::vector<float32> {
		0.2758038938,
			2.763578892,
			12.83915043,
			36.47584915,
			70.37084961,
			96.76893616,
			96.76893616,
			70.37084961,
			36.47584915,
			12.83915043,
			2.763578892,
			0.2758038938
	}, std::vector<float32> {
		1,
			7.605497837,
			27.34180641,
			60.83375549,
			92.60908508,
			100.8363876,
			79.74796295,
			45.49822617,
			18.1356678,
			4.690036297,
			0.6617552638,
			0.0281427335	  
	} };

	/**
	 * Upper-sideband filter coefficients. Generated with MATLAB 2015A.
	 */
	fparams F_UPPERSIDEBAND = { std::vector<float32> {
		0.001690387726,
			0.01145271584,
			0.03591799363,
			0.06576926261,
			0.0711934343,
			0.03156377375,
			-0.03156377375,
			-0.0711934343,
			-0.06576926261,
			-0.03591799363,
			-0.01145271584,
			-0.001690387726
	}, std::vector<float32> {
		1,
			9.465174675,
			41.62402725,
			112.0970993,
			205.2097626,
			267.9378662,
			254.4868011,
			175.7772827,
			86.5161972,
			28.89988136,
			5.897814751,
			0.5572910309
	} };


}

#endif
