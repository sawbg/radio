/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains a test program to test the Modulator class.
 * @bug Filtered SSB clicking
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

#include "auxiliary.hpp"
#include "Modulator.hpp"
#include "Sinusoid.hpp"
#include "PlTone.hpp"

using namespace std;
using namespace radio;

/**
 * Program to test the Modulator class.
 */
int main(int argc, char* argv[]) {

	// Constants
	const uint16 BUFFER_SIZE = 16384;

	// Declare primative Variables
	float32 dataBuffer[BUFFER_SIZE];
	float32 iqBuffer[2 * BUFFER_SIZE];
	ModulationType type;
	float32 freq = atof(argv[2]);
	float32 tone = 0;

	if(argc >= 4) tone = atof(argv[3]);

	try{
		type = to_type(string(argv[1]));
	} catch(std::exception ex) {
		std::cerr << ex.what() << std::endl << std::endl;
		return ERROR;
	}

	if(freq < 0) {
		cerr << "The given tone was invalid." << endl;
		return ERROR;
	}

	// Declare objects
	Modulator modulator(dataBuffer, BUFFER_SIZE, type, 20000);
	Sinusoid sinusoid(freq);
	PlTone(tone > 0 ? 0.15 : 0, dataBuffer, BUFFER_SIZE, tone, 48000);

	while(true) {
		for(uint16 i = 0; i < BUFFER_SIZE; i++) {
			dataBuffer[i] = sinusoid.next();
		}

		modulator.Mod();
		makeIQ(dataBuffer, iqBuffer, BUFFER_SIZE);
		to_sint32(iqBuffer, 2 * BUFFER_SIZE);
		write(STDOUT_FILENO, &iqBuffer,  2 * BUFFER_SIZE * sizeof(sint32));
	}
}
