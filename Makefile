all: keyboardio test

keyboardio:
	${MAKE} -C src/keyboardio

test:
	${MAKE} -C src/test

check: test
	${MAKE} -C src/test $@

clean:
	${MAKE} -C src/keyboardio clean
	${MAKE} -C src/test clean

.PHONY: all keyboardio test check clean
