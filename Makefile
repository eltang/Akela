VERBOSE							?= 0

ifneq (${VERBOSE}, 0)
SC									=
SS									= @ true ||
SR                  =
else
SC									= @
SS									= @
SR                  = | grep "\\(Program\\|Data\\):" | sed -e 's,^,  - ,' && echo
MAKEFLAGS += -s
endif

export SC
export SS
export SR

all: keyboardio test

keyboardio: keyboardio/Model01 keyboardio/stripped keyboardio/minimal keyboardio/example

keyboardio/%:
	${MAKE} -C lib/Akela-Model01/src/examples/$*

test:
	${SS} echo Building the test suite...
	${MAKE} -C test

check: test
	${SS} echo Running the test suite...
	${MAKE} -C test $@

clean:
	${SS} echo Cleaning in the firmwares ...
	${SC} rm -rf firmware
	${SS} echo Cleaning in test ...
	${SC} ${MAKE} -C test clean

.PHONY: all keyboardio test check clean
