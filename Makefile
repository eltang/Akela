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

keyboardio: keyboardio/Model01 keyboardio/stripped keyboardio/minimal

keyboardio/%:
	${MAKE} -C src/keyboardio/$*

test:
	${SS} echo Building the test suite...
	${MAKE} -C src/test

check: test
	${SS} echo Running the test suite...
	${MAKE} -C src/test $@

clean:
	${SS} echo Cleaning in the firmwares ...
	${SC} rm -rf firmware
	${SS} echo Cleaning in src/tets ...
	${SC} ${MAKE} -C src/test clean

.PHONY: all keyboardio test check clean
