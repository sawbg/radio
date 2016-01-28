#include <iostream>
#include <cstdio>

#include "modulation.hpp"

using namespace std;

int main() {
	const uint32 len = 8;
	float data[len];
//	DsbLcModulator mod(data, len*4);
	float temp;

	while(true) {
		for(int i = 0; i < len; i++) {
			scanf("%f", &data[i]);
		}

//		mod.Mod();

		for(int i = 0; i < len; i++) {
			printf("%f", data[i]);
		}

	}

}
