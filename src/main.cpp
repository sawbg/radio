/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains the "brains" of the entire project
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>

#include "auxiliary.hpp"
#include "Filter.hpp"
#include "Modulator.hpp"
#include "zdomain.hpp"

using namespace std;
using namespace radio;

int main(int argc, char* argv[]) {

	// Constants
	const uint8 ERROR = -1;
	const uint8 NUM_TYPES = 8;
	const uint16 BUFFER_SIZE = 16384;
	const float32 FREQ_MIN = 0;
	const float32 FREQ_MAX = 62;

	// Ensure 1 or 2 arguments given
	if(argc < 2) {
		std::cerr << "Error: too many arguments!" << std::endl;
		ShowHelp();
		return ERROR;
	} else if(argc > 3) {
		std::cerr << "Error: too few arguments!" << std::endl;
		ShowHelp();
		return ERROR;
	}

	// Declare primative Variables
	float32 dataBuffer[BUFFER_SIZE];
	float32 iqBuffer[2 * BUFFER_SIZE];
	ModulationType type;

	try{
		type = to_type(string(argv[1]));
	} catch(std::exception ex) {
		std::cerr << ex.what() << std::endl << std::endl;
		ShowHelp();
		return ERROR;
	}

	// Declare objects
	Filter baseFilter(dataBuffer, BUFFER_SIZE, F_BASEBAND);
	Modulator modulator(dataBuffer, BUFFER_SIZE, type, 5000);

	while(true) {
		read(STDIN_FILENO, &dataBuffer, BUFFER_SIZE * sizeof(float32));
		baseFilter.Pass();
		modulator.Mod();
		makeIQ(dataBuffer, iqBuffer, BUFFER_SIZE);
		write(STDOUT_FILENO, &iqBuffer,  2 * BUFFER_SIZE * sizeof(float32));
	}
}
