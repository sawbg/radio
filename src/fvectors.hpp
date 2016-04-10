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
	fparams F_BASEBAND = { std::vector<float64> {
		0.0008977019461,
			-0.002215694636,
			0.001372192986,
			0.001372192986,
			-0.002215694636,
			0.0008977019461	
	}, std::vector<float64> {
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
	fparams F_LOWERSIDEBAND = { std::vector<float64> {
		0.2758039069174,   
			2.763578787693,   
			12.83915022756,   
			36.47584850651,
			70.37084637368,   
			96.76893503179,   
			96.76893503179,   
			70.37084637368,
			36.47584850651,   
			12.83915022756,   
			2.763578787693,  
			0.2758039069174	  
	}, std::vector<float64> {
		1,
			7.605497780083,   
			27.34180552438,   
			60.83375457605,
			92.60908886875,       
			100.8363857,    
			79.74796574736,     
			45.4982252145,
			18.13566776308,    
			4.690036472717,   
			0.6617552879305,   
			0.0281427334611
	} };

	/**
	 * Upper-sideband filter coefficients. Generated with MATLAB 2015A.
	 */
	fparams F_UPPERSIDEBAND = { std::vector<float64> {
		0.001690387681463, 
			0.01145271586989, 
			0.03591799189724, 
			0.06576926098562,
			0.07119343282702,
			0.03156377419766,
			-0.03156377419766,
			-0.07119343282702,
			-0.06576926098562,
			-0.03591799189724,
			-0.01145271586989,
			-0.001690387681463
	}, std::vector<float64> {
		1,  
			9.465175013624,
			41.62402815905,
			112.0971027069,
			205.2097686473,    
			267.9378582311,     
			254.486805213,
			175.7772755115,
			86.51619894548,   
			28.89988093561,     
			5.89781461091,
			0.5572910543053	  
	} };


}

#endif
