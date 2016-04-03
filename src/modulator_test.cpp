/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains a test program to test the Modulator class
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

#include "auxiliary.hpp"
#include "Modulator.hpp"

using namespace std;
using namespace radio;

/**
 * Program to test the Modulator class with a self-generated sinusoidal input.
 */
int main(int argc, char* argv[]) {

	// Constants
	const uint8 ERROR = -1;
	const uint16 BUFFER_SIZE = 16384;

	// Declare primative Variables
	float32 dataBuffer[BUFFER_SIZE];
	float32 iqBuffer[2 * BUFFER_SIZE];
	ModulationType type;
	float32 freq = atof(argv[2]);

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
	Modulator modulator(dataBuffer, BUFFER_SIZE, type, 5000);
	Sinusoid sinusoid(freq);

	while(true) {
		for(uint16 i = 0; i < BUFFER_SIZE; i++) {
			dataBuffer[i] = sinusoid.next();
		}

		modulator.Mod();
		makeIQ(dataBuffer, iqBuffer, BUFFER_SIZE);
		write(STDOUT_FILENO, &iqBuffer,  2 * BUFFER_SIZE * sizeof(float32));
	}
}
