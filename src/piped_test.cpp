/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief containts the original program used to test the piping-in idea
 */

#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "Filter.hpp"
#include "modulation.hpp"
#include "zdomain.hpp"

using namespace std;
using namespace lolz;

/**
 * Program originally used to test whether baseband audio could be piped into
 * the program in real time.
 */
int main() {
	const uint16 len = 16384;
	float32 data[len];
	float32 iqData[2*len];

	while(true) {
		read(STDIN_FILENO, &data, len * sizeof(float32));
		makeIQ(data, iqData, len);
		write(STDOUT_FILENO, &iqData,  2 * len * sizeof(float32));
	}

}
