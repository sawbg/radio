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
#include "Subcarrier.hpp"
#include "Modulator.hpp"
#include "zdomain.hpp"

using namespace std;
using namespace radio;

/**
 * Final result of the entire project. Completes all goals and more!
 */
int main(int argc, char* argv[]) {

	// Constants
	const uint8 ERROR = -1;
	const uint8 NUM_TYPES = 8;
	const uint16 BUFFER_SIZE = 16384;
	const uint32 SAMPLING_RATE = 48000;

	// Ensure 1 or 2 arguments given
	if(argc > 3) {
		std::cerr << "Error: too many arguments!" << std::endl;
		ShowHelp();
		return ERROR;
	} else if(argc < 2) {
		std::cerr << "Error: too few arguments!" << std::endl;
		ShowHelp();
		return ERROR;
	}

	// Declare primative Variables
	float32 toneFreq = 0;
	float32 dataBuffer[BUFFER_SIZE];
	float32 iqBuffer[2 * BUFFER_SIZE];
	ModulationType type;

	// validate modulation type
	try{
		type = to_type(string(argv[1]));
	} catch(std::exception ex) {
		std::cerr << "The given modulation type is invalid!" << std::endl;
		ShowHelp();
		return ERROR;
	}

	// validate CTCSS tone
	if(argc == 3) {
		try {
			toneFreq = std::stof(argv[2]);

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
	Modulator modulator(dataBuffer, BUFFER_SIZE, type, 20000);
	Subcarrier pltone(0.15, dataBuffer, BUFFER_SIZE, toneFreq, SAMPLING_RATE);

	while(true) {
		read(STDIN_FILENO, &dataBuffer, BUFFER_SIZE * sizeof(float32));

		for(uint32 i = 0; i < BUFFER_SIZE; i++) {
//			dataBuffer[i] *= 2;
		}

		baseFilter.Pass();
		pltone.Add();
		modulator.Mod();
		makeIQ(dataBuffer, iqBuffer, BUFFER_SIZE);
		to_sint32(iqBuffer, 2 * BUFFER_SIZE);
		write(STDOUT_FILENO, &iqBuffer,  2 * BUFFER_SIZE * sizeof(float32));
	}
}
