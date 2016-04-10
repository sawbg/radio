/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains the "brains" of the entire project
 */

#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

#include "auxiliary.hpp"
#include "Filter.hpp"
#include "Gain.hpp"
#include "Modulator.hpp"
#include "PlTone.hpp"
#include "zdomain.hpp"

using namespace std;
using namespace radio;

/**
 * Final result of the entire project. Completes all goals and more!
 */
int main(int argc, char* argv[]) {

	// Constants
	const uint8 NUM_TYPES = 8;
	const uint16 BUFFER_SIZE = 16384;
	const uint32 BUFFER_BYTE_COUNT = BUFFER_SIZE * sizeof(sint32);
	const uint32 IQ_BUFFER_SIZE = 2 * BUFFER_SIZE;
	const uint32 IQ_BUFFER_BYTE_COUNT = BUFFER_BYTE_COUNT * 2;
	const uint32 SAMPLING_RATE = 48000;

	// Ensure 1 or 2 arguments given
	if(argc > 4) {
		std::cerr << "Error: too many arguments!" << std::endl;
		ShowHelp();
		return ERROR;
	} else if(argc < 2) {
		std::cerr << "Error: too few arguments!" << std::endl;
		ShowHelp();
		return ERROR;
	}

	// Declare primative Variables
	float32 micGain = 0;
	float32 toneFreq = 0;
	float32 dataBuffer[BUFFER_SIZE];
	float32 iqBuffer[IQ_BUFFER_SIZE];
	ModulationType type;

	// validate modulation type
	try{
		type = to_type(string(argv[1]));
	} catch(std::exception ex) {
		std::cerr << "The given modulation type is invalid!" << std::endl;
		ShowHelp();
	}

	// process mic gain
	if(argc >= 3) {
		try {
			micGain = std::stof(argv[2]);
		} catch(std::invalid_argument ex) {
			std::cerr << "The specified microphone gain is not a number."
				<< std::endl;
			ShowHelp();
		}
	}

	// validate CTCSS tone
	if(argc == 4) {
		try {
			toneFreq = std::stof(argv[3]);

			if(toneFreq < 60 || toneFreq > 260) {
				throw std::out_of_range("");
			}
		} catch(std::out_of_range ex) {
			std::cerr << "The specified CTCSS frequency is outside of the "
				"standard PL tone range." << std::endl;
			ShowHelp();
		} catch(std::invalid_argument ex) {
			std::cerr << "The specified CTCSS frequency is not a number."
				<< std::endl;
			ShowHelp();
		}
	}

	// Declare objects
	Filter baseFilter(dataBuffer, BUFFER_SIZE, F_BASEBAND);
	Gain gain(dataBuffer, BUFFER_SIZE, micGain);
	PlTone pltone(0.15, dataBuffer, BUFFER_SIZE, toneFreq, SAMPLING_RATE);
	Modulator modulator(dataBuffer, BUFFER_SIZE, type, 20000);

	// SDR guts of the program
	while(true) {
		// get next samples
		read(STDIN_FILENO, &dataBuffer, BUFFER_BYTE_COUNT);
		
		// process/modulate samples
		baseFilter.Pass();
//		pltone.Add();
		gain.Apply();
		modulator.Mod();
		makeIQ(dataBuffer, iqBuffer, BUFFER_SIZE);
		to_sint32(iqBuffer, IQ_BUFFER_SIZE);
		
		// write samples
		write(STDOUT_FILENO, &iqBuffer, IQ_BUFFER_BYTE_COUNT);
	}
}
