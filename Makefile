VERBOSE							?=

ifeq (${VERBOSE}, 1)
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
	${SC} echo Building the test suite...
	${MAKE} -C src/test

check: test
	${SC} echo Running the test suite...
	${MAKE} -C src/test $@

clean:
	${SS} echo Cleaning in src/keyboardio ...
	${SC} find src/keyboardio -name firmware -type d | xargs rm -rf
	${SS} echo Cleaning in src/tets ...
	${SC} ${MAKE} -C src/test clean

.PHONY: all keyboardio test check clean
