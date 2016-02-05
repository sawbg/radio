#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "Filter.hpp"
#include "modulation.hpp"
#include "zdomain.hpp"

using namespace std;
using namespace lolz;

int main() {
	const uint16 len = 16384;
	float32 data[len];
	float32 iqData[2*len];
	DsbScModulator mod(data, len);

	vector<vector<float32>> baseFilterVector = { vector<float32> {


	Filter baseFilter;


	for(int i = 0; i < len; i++) {
		//data[i] = sin(2*3.141592*440*i/len);
	}



	while(true) {
		read(STDIN_FILENO, &data, len * sizeof(float32));
		//mod.Mod();
		makeIQ(data, iqData, len);
		write(STDOUT_FILENO, &iqData,  2 * len * sizeof(float32));
	}

}
