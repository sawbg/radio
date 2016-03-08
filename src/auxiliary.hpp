/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains helper-functions for main()
 */

#ifndef auxiliary_H
#define auxiliary_H

#include <iostream>

#include "definitions.hpp"

namespace radio {

	/**
	 *
	 */
	void ShowHelp() {
		std::cerr << "Usage: radio [FREQUENCY] [MODE] [PL TONE]" << std::endl
			<< std::endl
			<< "FREQUENCY: the desired transmit frequency in MHz "
			"from 0-62 MHz" << std::endl
			<< "MODE: one of the following types"
			"of modulation" << std::endl << std::endl;

		std::cerr << "dsblc\t\tDouble sideband, large carrier" << std::endl
			<< "am\t\tAlias for dsblc" << std::endl
			<< "dsbsc\t\tDouble sideband, suppressed carrier" << std::endl
			<< "lsbhil\t\tLower sideband created via Hilbert transform"
			<< std::endl
			<< "lsbfilt\t\tLower sideband created via digital low-pass filter"
			<< std::endl
			<< "usbhil\t\tUpper sideband created via Hilbert transform"
			<< std::endl
			<< "usbfilt\t\tUpper sideband created via digital high-pass filter"
			<< std::endl
			<< "fm2.5k\t\tFrequency modulation, 2.5 kHz bandwidth"
			<< std::endl
			<< "fm5k\t\t Frequency modulation, 5 kHz bandwidth" << std::endl;

		std::cerr << "PL TONE: Optional specification for CTCSS tone from "
			"0-300 Hz" << std::endl << std::endl;
	}
}

#endif
