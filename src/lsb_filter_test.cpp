/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains a program to test the LSB-via-filter implementation
 */

#include <iostream>
#include <cmath>
#include <cstdio>
#include <unistd.h>

#include "definitions.hpp"
#include "Filter.hpp"
#include "fvectors.hpp"
#include "zdomain.hpp"

using namespace std;
using namespace radio;

/**
 * Tests an implementation of LSB modulation through a filter.
 */
int main() {
	const uint32 len = 65536;
	float32 data[len];
	float32 temp[len];
	Filter baseFilter(temp, len, F_LOWERSIDEBAND);

	for(int i = 0; i < len; i++) {
		data[i] = 0.95 * (sin(2*M_PI*440*i/48000)
				+ sin(2*M_PI*2000*i/48000) + sin(2*M_PI*2500*i/48000)
				+ sin(2*M_PI*3000*i/48000));
	}

	while(true) {
		for(int i = 0; i < len; i++) {
			temp[i] = data[i];
		}

		baseFilter.Pass();
		write(STDOUT_FILENO, &temp,  len * sizeof(float32));
	}

}
