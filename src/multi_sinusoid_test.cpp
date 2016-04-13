/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains a program to demonstrate the ability of the Sinusoid class
 * and the sound card to generate sinusoids accross the spectrum.
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

#include "auxiliary.hpp"
#include "definitions.hpp"
#include "Sinusoid.hpp"
#include "zdomain.hpp"

using namespace std;
using namespace radio;

/**
 * Program to test the Sinusoid class and demonstrate the frequency range of the
 * sound card.
 */
int main(int argc, char* argv[]) {

	// Constants
	const uint16 BUFFER_SIZE = 48000;

	// Declare primative Variables
	uint8 i = 0;
	uint8 size = 0;
	uint16 delta = 100;
	float32 dataBuffer[BUFFER_SIZE];
	float32 iqBuffer[2 * BUFFER_SIZE];

	for(uint16 f = 100; f < 24000; f += delta, i++) {
		Sinusoid sinusoid(f);

		for(uint16 i = 0; i < BUFFER_SIZE; i++) {
			dataBuffer[i] += sinusoid.next();
		}

		switch(f) {
			case 500:
				delta = 1000;
				f = 1000;
				break;

			case 2000:
				delta = 2000;
				break;
		}
	}

	size = i;
	
	for(uint16 i = 0; i < BUFFER_SIZE; i++) {
		dataBuffer[i] /= size;
	}
	
	makeIQ(dataBuffer, iqBuffer, BUFFER_SIZE);
	to_sint32(iqBuffer, 2 * BUFFER_SIZE);

	while(true) {
		write(STDOUT_FILENO, &iqBuffer, 2 * BUFFER_SIZE * sizeof(sint32));
	}
}
