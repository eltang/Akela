CXXFLAGS = -I../lib/Akela/src \
           -I../lib/Akela-TapDance/src \
           -I. \
           -include util/Arduino-compat.h \
           -std=c++11 \
           -O0 -ggdb3 \
           -Wall -Wno-unused-variable -Woverloaded-virtual

ifeq (${VERBOSE},2)
_r =
else
_r = >/dev/null
endif

all: AkelaTest
check: all
	./AkelaTest | sed -e 's# \*, #\*, #g' | tee test.out ${_r}
	diff -u test.expected test.out

AKELA_SOURCES = \
	../lib/Akela/src/Akela/Keyboard.cpp \
	../lib/Akela/src/Akela/KeyMap/Basic.cpp \
	../lib/Akela/src/Akela/KeyMap/Layered.cpp \
	../lib/Akela/src/Akela/EventHandler/Base.cpp \
	../lib/Akela/src/Akela/EventHandler/Components/Layer.cpp \
	../lib/Akela/src/Akela/EventHandler/Components/FnMacro.cpp \
	../lib/Akela/src/Akela/EventHandler/Layered.cpp \
	../lib/Akela-TapDance/src/Akela/TapDance/Component/OneShot.cpp \
	../lib/Akela-TapDance/src/Akela/TapDance/Component/OneShotMod.cpp \
	../lib/Akela-TapDance/src/Akela/TapDance/Component/OneShotLayer.cpp \
	../lib/Akela-TapDance/src/Akela/TapDance/Component/TapDance.cpp
AKELA_HEADERS = \
	${AKELA_SOURCES:.cpp=.h} \
	../lib/Akela/src/Akela.h \
	../lib/Akela/src/Akela/AbstractHID.h \
	../lib/Akela/src/Akela/KeyCodes.h \
	../lib/Akela/src/Akela/SysFn.h \
	../lib/Akela/src/Akela/AbstractScanner.h \
	../lib/Akela/src/Akela/EventHandler/Component.h \
	../lib/Akela-TapDance/src/Akela-TapDance.h

TEST_SOURCES = \
	AkelaTest.cpp \
	TestCases/BasicKeyPresses.cpp \
	TestCases/Layers.cpp \
	TestCases/FnMacros.cpp \
	util/scanners.cpp \
	Virtual/HID.cpp \
	Virtual/Keyboard.cpp \
	Virtual/EventHandler.cpp \
	Virtual/KeyMap.cpp \
	Virtual/Scanner.cpp

TEST_HEADERS = \
	util/Arduino-compat.h

AkelaTest: ${TEST_SOURCES} ${AKELA_SOURCES} ${AKELA_HEADERS} ${TEST_HEADERS}
	${CXX} ${CXXFLAGS} ${AKELA_SOURCES} AkelaTest.cpp -o $@

clean:
	rm -f AkelaTest test.out

.PHONY: all clean check
