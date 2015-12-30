GCC = g++-4.9
CPPFLAGS = -g -std=gnu++14

fft-test.cpp
	$(GCC) src/fft_test.cpp -o bin/fft-test $(CPPFLAGS)

docs:
	rm -r doc/
	doxygen etc/doxygen.config
	git reset
	git add doc/.
	git commit -m "Updated documentation."
	git push

count:
	find src/ -name '*' | xargs wc -l  # works assuming there's no subdirectories
