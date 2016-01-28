#include <iostream>
#include <cstdio>

#include "modulation.hpp"

using namespace std;

int main() {
	unsigned char data[16384];
//	DsbLcModulator mod(data, 16384);
//	unsigned char* loc;
//	unsigned char temp;

	while(true) {
		char* pt1 = (char*) &data;
		const char * pt2 = (const char*) &data;
		cin.get(pt1, 16384);
		cout.write(pt2, 16384);
	}

}
