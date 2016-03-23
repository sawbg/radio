/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains helper-functions for main()
 */

#ifndef auxiliary_H
#define auxiliary_H

#include <iostream>
#include <stdexcept>
#include <string>

#include "definitions.hpp"

namespace radio {

	/**
	 *
	 */
	void ShowHelp() {
		std::cerr << "Usage: radio [MODE] [PL TONE]" << std::endl
			<< std::endl
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
			<< "nfm\t\tFrequency modulation, 2.5 kHz bandwidth"
			<< std::endl
			<< "wfm\t\tFrequency modulation, 5 kHz bandwidth" << std::endl
			<< "fm\t\talias for wfm" << std::endl;

		std::cerr << "PL TONE: Optional specification for CTCSS tone from "
			"60-260 Hz" << std::endl << std::endl;
	}

	/**
	 *
	 */
	ModulationType to_type(std::string str) {
		ModulationType type;

		if(str == "dsblc" || str == "am") {
			type = ModulationType::DSB_LC;
		} else if(str == "dsbsc") {
			type = ModulationType::DSB_SC;
		} else if(str == "lsbhil") {
			type = ModulationType::LSB_HILBERT;
		} else if(str == "lsbfilt") {
			type = ModulationType::LSB_FILTERED;
		} else if(str == "usbhil") {
			type = ModulationType::USB_HILBERT;
		} else if(str == "usbfilt") {
			type = ModulationType::USB_FILTERED;
		} else if(str == "wfm" || str == "fm") {
			type = ModulationType::FM_NARROW;
		} else if(str == "nfm") {
			type = ModulationType::FM_WIDE;
		} else {
			throw std::logic_error("The given modulation type is invalid!");
		}

		return type;
	}
}

#endif
