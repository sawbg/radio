/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains a test program to test the PlTone class.
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

#include "auxiliary.hpp"
#include "PlTone.hpp"
#include "zdomain.hpp"

using namespace std;
using namespace radio;

/**
 * Program to test the PlTone class.
 */
int main(int argc, char* argv[]) {
	// Constants
	const uint16 BUFFER_SIZE = 16384;

	// Declare primative Variables
	float32 dataBuffer[BUFFER_SIZE];
	float32 iqBuffer[2 * BUFFER_SIZE];
	float32 freq = atof(argv[1]);

	if(freq < 0) {
		cerr << "The given tone was invalid." << endl;
		return ERROR;
	}

	PlTone tone(0.15, dataBuffer, BUFFER_SIZE, freq, 48000);

	while(true) {
		for(uint16 i = 0; i < BUFFER_SIZE; i ++) {
			dataBuffer[i] = 1;
		}
		
		tone.Add();
		makeIQ(dataBuffer, iqBuffer, BUFFER_SIZE);
		to_sint32(iqBuffer, 2 * BUFFER_SIZE);
		write(STDOUT_FILENO, &iqBuffer, 2 * BUFFER_SIZE * sizeof(sint32));
	}
}
