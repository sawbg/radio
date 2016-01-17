#include <cmath>
#include <climits>
#include <iostream>
#include <alsa/asoundlib.h>

#include "definitions.hpp"

using namespace std;

int main() {
	int ret;

	snd_pcm_t* pcm_handle;  // device handle
	snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK;
	//	snd_pcm_stream_t stream = SND_PCM_STREAM_CAPTURE;
	snd_pcm_hw_params_t* hwparams;  // hardware information
	//char* pcm_name = strdup("plughw:1,0");  // on-board audio jack
	char* pcm_name = strdup("plughw:1,0");  // on-board audio jack
	int rate = 48000;

	const uint16 freq = 440;
	long unsigned int bufferSize = 65536*4;  // anything >8192 causes seg fault
	const uint32 len = bufferSize*100;
	const float32 arg = 2 * 3.141592 * freq / rate;
	sint16 vals[len];

	float test;
	double last = 0;
	long unsigned int count = 0;

	for(uint32 i = 0; i < len; i = i + 2) {
		test = 32000 * cos(last);
		vals[i] = (sint16)(test + 0.5);
		vals[i+1] = vals[i];
	}

	cout << "COUNT: " << count << endl;
	snd_pcm_hw_params_alloca(&hwparams);

	ret = snd_pcm_open(&pcm_handle, pcm_name, stream, 0);
	cout << "Opening: " << snd_strerror(ret) << endl;

	ret = snd_pcm_hw_params_any(pcm_handle, hwparams);
	cout << "Initializing hwparams structure: " << snd_strerror(ret) << endl;	

	ret = snd_pcm_hw_params_set_access(pcm_handle, hwparams,
			SND_PCM_ACCESS_RW_INTERLEAVED);
	cout << "Setting access: " << snd_strerror(ret) << endl;

	ret = snd_pcm_hw_params_set_format(pcm_handle, hwparams,
			SND_PCM_FORMAT_S16_LE);
	cout << "Setting format: " << snd_strerror(ret) << endl;

	ret = snd_pcm_hw_params_set_rate(pcm_handle, hwparams,
			rate, (int)0);
	cout << "Setting rate: " << snd_strerror(ret) << endl;

	ret = snd_pcm_hw_params_set_channels(pcm_handle, hwparams, 2); 
	cout << "Setting channels: " << snd_strerror(ret) << endl;

	ret = snd_pcm_hw_params_set_periods(pcm_handle, hwparams, 4, 0);
	cout << "Setting periods: " << snd_strerror(ret) << endl;

	ret = snd_pcm_hw_params_set_buffer_size_near(pcm_handle, hwparams,
			&bufferSize);
	cout << "Setting buffer size: "	<< snd_strerror(ret) << endl;

	ret = snd_pcm_hw_params(pcm_handle, hwparams);
	cout << "Applying parameters: "	<< snd_strerror(ret) << endl;

	ret = snd_pcm_hw_params_get_buffer_size(hwparams, &count);
	cout << "Actual period size: " << count << endl;
	cout << "Returned: " << snd_strerror(ret) << endl;



	cout << endl << endl;


	const void* ptr[100];

	for(int i = 0; i < 100; i++) {
		ptr[i] = (const void*)&vals + bufferSize*i;
	}

	int err;

	for(int i = 0; i < 100; i++) {
		do {
			ret = snd_pcm_writei(pcm_handle,
					ptr[i], bufferSize);

			if(ret < 0) {
				err = snd_pcm_prepare(pcm_handle);
				cout << "Preparing: " << snd_strerror(err)
					<< endl;
			}
		} while(ret < 0);

		cout << "Writing data: " << ret << endl;
	}
}
