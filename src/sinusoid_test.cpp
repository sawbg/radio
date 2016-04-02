/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains a test program to test the Sinusoid class
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
 *
 */
int main(int argc, char* argv[]) {

	// Constants
	const uint8 ERROR = -1;
	const uint16 BUFFER_SIZE = 16384;

	// Declare primative Variables
	float32 dataBuffer[BUFFER_SIZE];
	float32 freq = atof(argv[1]);

	if(freq < 0) {
		cerr << "The given tone was invalid." << endl;
		return ERROR;
	}

	Sinusoid sinusoid(freq);

	while(true) {
		for(uint16 i = 0; i < BUFFER_SIZE; i++) {
			dataBuffer[i] = sinusoid.next();
		}

		write(STDOUT_FILENO, &dataBuffer, BUFFER_SIZE * sizeof(float32));
	}
}
