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

piped-test:
	$(GCC) $(CPPFLAGS) src/piped_test.cpp -o bin/pipedtest
