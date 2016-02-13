GCC = g++
CPPFLAGS = -g -std=gnu++14 

alsa-test:
	$(GCC) $(CPPFLAGS) src/alsa_test.cpp -o bin/alsatest -O0 -lasound

baseband-filter-test:
	$(GCC) $(CPPFLAGS) src/baseband_filter_test.cpp -o bin/bbftest

count:
	find src/ -name '*' | xargs wc -l  # works assuming there's no subdirectories

docs:
	rm -r doc/
	doxygen etc/doxygen.config
	git reset
	git add doc/.
	git commit -m "Updated documentation."
	git push

fft-test:
	$(GCC) $(CPPFLAGS) src/fft_test.cpp -o bin/fft-test

fft-test2:
	$(GCC) $(CPPFLAGS) src/fft_test2.cpp -o bin/fft-test2

iq-test:
	$(GCC) $(CPPFLAGS) src/iq_test.cpp -o bin/iqtest
