#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "Filter.hpp"
#include "modulation.hpp"
#include "zdomain.hpp"

using namespace std;
using namespace radio;

int main() {
	
	
	
	
	
	
	const uint16 len = 16384;
	float32 data[len];
	float32 iqData[2*len];
	Filter baseFilter;

	while(true) {
		read(STDIN_FILENO, &data, len * sizeof(float32));
		//mod.Mod();
		makeIQ(data, iqData, len);
		write(STDOUT_FILENO, &iqData,  2 * len * sizeof(float32));
	}
}
