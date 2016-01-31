#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "modulation.hpp"

using namespace std;
using namespace lolz;

int main() {
	const uint16 len = 48000;
	float32 data[len];
	uint16 index = 0;
	float32 vals[48000];

	for(int i = 0; i < 48000; i++) {
		vals[i] = cos(2*M_PI*20000*(float)i/48000);
	}

	for(int i = 0; i <= 3; i++) {
		cerr << "header" << endl;
		putchar((int)255);
	}

	while(true) {
		cerr << "loop" << endl;
	
		for(int i = 0; i < len; i++) {
			//data[i] = (uint8)getchar();
			if(index >= 48000) index = 0;
//			read(STDIN_FILENO, &data, len);
		}

//		mod.Mod();

		for(int i = 0; i < len; i++) {
			write(STDOUT_FILENO, &vals, len);
		}

	}

}
