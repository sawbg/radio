/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains a program to demonstrate the the LSB/AF filter.
 * @bug Clicking occurs at start of each filter pass
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "auxiliary.hpp"
#include "definitions.hpp"
#include "Filter.hpp"
#include "fvectors.hpp"
#include "Sinusoid.hpp"
#include "zdomain.hpp"

using namespace std;
using namespace radio;

/**
 * Program to test the Filter class and the LSB filter coefficients.
 */
int main(int argc, char* argv[]) {

	// Constants
	const uint16 BUFFER_SIZE = 48000;

	// Declare primative Variables
	uint8 i = 0;
	uint8 size = 0;
	uint16 delta = 250;
	float32 dataBuffer[BUFFER_SIZE];
	float32 iqBuffer[2 * BUFFER_SIZE];

	// create 1 sec of audio
	for(uint16 f = 17000; f <= 23000; f += delta, i++) {
		Sinusoid sinusoid(f);

		for(uint16 i = 0; i < BUFFER_SIZE; i++) {
			dataBuffer[i] += sinusoid.next();
		}
	}

	size = i;
	
	// adjust dataBuffer so values are between -1 and 1
	for(uint16 i = 0; i < BUFFER_SIZE; i++) {
		dataBuffer[i] /= size;
	}
	
	Filter filter(dataBuffer, BUFFER_SIZE, F_LOWERSIDEBAND);
	filter.Pass();
	makeIQ(dataBuffer, iqBuffer, BUFFER_SIZE);
	to_sint32(iqBuffer, 2 * BUFFER_SIZE);

	while(true) {
		write(STDOUT_FILENO, &iqBuffer, 2 * BUFFER_SIZE * sizeof(sint32));
	}
}
