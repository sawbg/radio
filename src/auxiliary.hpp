/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains helper-functions for main().
 */

#ifndef auxiliary_H
#define auxiliary_H

#include <climits>
#include <iostream>
#include <stdexcept>
#include <string>

#include "definitions.hpp"

namespace radio {

	/**
	 * Displays the help information and exits the program.
	 */
	void ShowHelp() {
		std::cerr << std::endl << "Usage: radio [MODE] [MIC GAIN] "
			"[PL TONE]" << std::endl << std::endl
			<< "MODE: one of the following types "
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
//			<< "nfm\t\tFrequency modulation, 2.5 kHz bandwidth"
			<< std::endl;
//			<< "wfm\t\tFrequency modulation, 5 kHz bandwidth" << std::endl
//			<< "fm\t\talias for wfm" << std::endl << std::endl;

		std::cerr << "MIC GAIN: Microphone power gain expressed in decibels"
		<< std::endl << std::endl;

		std::cerr << "PL TONE: Optional specification for CTCSS tone from "
			"60-260 Hz" << std::endl << std::endl;

		std::exit(ERROR);
	}

	/**
	 * Replaces float32 samples with sint32 equivalents. Rounds conversion to
	 * nearest integer.
	 *
	 * @param data the array containing the float32 samples that are directly
	 * replaced by their respective sint32 representations
	 *
	 * @param size the number of elements in the data array
	 */
	void to_sint32(float32* data, uint32 size) {
		for(uint32 i = 0; i < size; i++) {
			((sint32*)data)[i] = (sint32)(data[i] * INT_MAX + 0.5);
		}
	}

	/**
	 * Converts a string representation of the supported modulation types (see
	 * ShowHelp() documentation) to the enum class ModulationType value.
	 *
	 * This function is not as elegant as it could be. Ideally, I would have
	 * used a std::map<string, ModulationType> rather than a long series of
	 * if-else's.
	 *
	 * @param str type of modulation in typed form
	 *
	 * @return enum value of the type of modulation
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
