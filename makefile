GCC = g++ -g -std=gnu++14

alsa-test:
	$(GCC) src/alsa_test.cpp -o bin/alsatest -O0 -lasound

baseband-filter-test:
	$(GCC) src/baseband_filter_test.cpp -o bin/bbftest

count:
	grep -r "src/" -e "Samuel Andrew Wisner" -l | xargs wc -l

docs:
	rm -r doc/
	doxygen etc/doxygen.config
	cd doc/latex; make pdf;
	git reset
	git add doc/.
	git commit -m "Updated documentation."
	git push

fft-test:
	$(GCC) src/fft_test.cpp -o bin/fft-test

fft-test2:
	$(GCC) src/fft_test2.cpp -o bin/fft-test2

iq-test:
	$(GCC) src/iq_test.cpp -o bin/iqtest

modulator-test:
	$(GCC) src/modulator_test.cpp -o bin/modulatortest

lsb-filter-test:
	$(GCC) src/lsb_filter_test.cpp -o bin/lsbftest

radio:
	$(GCC) src/main.cpp -o bin/sdr

sinusoid-test:
	$(GCC) src/sinusoid_test.cpp -o bin/sinusoidtest
