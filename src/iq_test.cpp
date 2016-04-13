/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Generates test IQ signal.
 */

#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "zdomain.hpp"

using namespace std;
using namespace radio;

/**
 * This small program demonstrates the IQ generation abilities of the makeIQ()
 * function.
 */
int main() {
	const uint16 len = 16384;
	float32 data[len];
	float32 iqData[2*len];

	for(int i = 0; i < len; i++) {
		data[i] = sin(2*3.141592*170*i/len);
	}

	while(true) {
		read(STDIN_FILENO, &data, len * sizeof(float32));
		makeIQ(data, iqData, len);
		write(STDOUT_FILENO, &iqData,  2 * len * sizeof(float32));
	}
}
