#include <iostream>
#include <cmath>
#include <cstdio>
#include <unistd.h>

#include "definitions.hpp"
#include "Filter.hpp"
#include "fvectors.hpp"
#include "zdomain.hpp"

using namespace std;
using namespace lolz;

int main() {
	const uint16 len = 16384;
	float32 data[len];
	Filter baseFilter(data, len, F_BASEBAND);

	for(int i = 0; i < len; i++) {
		data[i] = 0.25 * (sin(2*M_PI*440*i/48000)
				+ sin(2*M_PI*2000*i/48000) + sin(2*M_PI*2500*i/48000)
				+ sin(2*M_PI*3000*i/48000));
	}

	while(true) {
		baseFilter.Pass();
		write(STDOUT_FILENO, &data,  len * sizeof(float32));
	}

}
