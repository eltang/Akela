all: arduino test

arduino:
	${MAKE} -C src/arduino

test:
	${MAKE} -C src/test

check: test
	${MAKE} -C src/test $@

clean:
	${MAKE} -C src/arduino clean
	${MAKE} -C src/test clean

.PHONY: all arduino test check clean
