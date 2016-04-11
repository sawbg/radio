GCC = g++ -g -std=gnu++14

alsa-test:
	$(GCC) src/alsa_test.cpp -o bin/alsatest -O0 -lasound

baseband-filter-test:
	$(GCC) src/baseband_filter_test.cpp -o bin/basebandfiltertest

count:
	grep -r "src/" -e "Samuel Andrew Wisner" -l | xargs wc -l

docs:
	rm -r doc/
	doxygen etc/doxygen.config
	cd doc/latex; make pdf;
	git reset
	git add doc/.
	git --no-pager log > etc/log.txt
	git add etc/log.txt
	git commit -m "Updated documentation."
	git push

fft-test:
	$(GCC) src/fft_test.cpp -o bin/fft-test

fft-test2:
	$(GCC) src/fft_test2.cpp -o bin/fft-test2

iq-test:
	$(GCC) src/iq_test.cpp -o bin/iqtest

multi-sinusoid-test:
	$(GCC) src/multi_sinusoid_test.cpp -o bin/multisinusoidtest

modulator-test:
	$(GCC) src/modulator_test.cpp -o bin/modulatortest

lsb-filter-test:
	$(GCC) src/lsb_filter_test.cpp -o bin/lsbftest

pl-tone-test:
	$(GCC) src/pl_tone_test.cpp -o bin/pltonetest

radio:
	$(GCC) src/main.cpp -o bin/sdr

sinusoid-test:
	$(GCC) src/sinusoid_test.cpp -o bin/sinusoidtest
