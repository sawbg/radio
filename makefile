GCC = g++
CPPFLAGS = -g -std=gnu++14 

alsa-test:
	$(GCC) $(CPPFLAGS) src/alsa_test.cpp -o bin/alsatest -O0 -lasound

docs:
	rm -r doc/
	doxygen etc/doxygen.config
	git reset
	git add doc/.
	git commit -m "Updated documentation."
	git push

count:
	find src/ -name '*' | xargs wc -l  # works assuming there's no subdirectories

fft-test:
	$(GCC) $(CPPFLAGS) src/fft_test.cpp -o bin/fft-test

fft-test2:
	$(GCC) $(CPPFLAGS) src/fft_test2.cpp -o bin/fft-test2


piped-test:
	$(GCC) $(CPPFLAGS) src/piped_test.cpp -o bin/pipedtest
