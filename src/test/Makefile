CXXFLAGS = -I../../lib/Akela -I. -O0 -ggdb3 -Wall -Wno-unused-variable

ifeq (${VERBOSE},1)
_r =
else
_r = >/dev/null
endif

all: AkelaTest
check: all
	./AkelaTest | tee test.out ${_r}
	diff -u test.out test.expected

AKELA_SOURCES = \
	../../lib/Akela/AkelaKeyboard.cpp \
	../../lib/Akela/AkelaKeyMap.cpp \
	../../lib/Akela/AkelaKeyEventHandler.cpp
AKELA_HEADERS = \
	${AKELA_SOURCES:.cpp=.h} \
	../../lib/Akela/Akela.h \
	../../lib/Akela/AkelaAbstractHID.h \
	../../lib/Akela/AkelaKeyCodes.h

TEST_SOURCES = AkelaTest.cpp TestBasics.cpp TestMods.cpp TestFn.cpp

TEST_HEADERS = Tests.h TestCommon.h PrinterHID.h PrinterKeymap.h \
	TestKeymaps.h PressReleaseKb.h PrinterFnHandler.h

AkelaTest: ${TEST_SOURCES} ${AKELA_SOURCES} ${AKELA_HEADERS} ${TEST_HEADERS}
	${CXX} ${CXXFLAGS} ${AKELA_SOURCES} ${TEST_SOURCES} -o $@

clean:
	rm -f AkelaTest test.out

.PHONY: all clean check
