#ifndef fvectors_H
#define fvectors_H

#include <vector>

#include "definitions.hpp"

typedef std::vector<std::vector<float32>> fparams;

namespace lolz {
	fparams F_BASEBAND = { std::vector<float32> {
		0.0008977019461,
			-0.002215694636,
			0.001372192986,
			0.001372192986,
			0.002215694636,
			0.0008977019461
	}, std::vector<float32> {
		1,
			-4.678616047,
			8.822912216,
			-8.379911423,
			4.007629871,
			-0.7719064355
	} };
}

#endif
