#include <iostream>
#include <cstdio>

#include "modulation.hpp"

using namespace std;

int main() {
	const uint16 len = 256;
	uint8 data[len];
	DsbLcModulator mod(data, len);

	while(true) {
		for(int i = 0; i < len; i++) {
			data[i] = (uint8)getchar();
		}

		mod.Mod();

		for(int i = 0; i < len; i++) {
			putchar((int)data[i]);
		}

	}

}
