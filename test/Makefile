CXXFLAGS = -I../lib/Akela/src -I. -O0 -ggdb3 -Wall -Wno-unused-variable -std=c++11 -Woverloaded-virtual

ifeq (${VERBOSE},2)
_r =
else
_r = >/dev/null
endif

all: AkelaTest
check: all
	./AkelaTest | tee test.out ${_r}
	diff -u test.expected test.out

AKELA_SOURCES = \
	../lib/Akela/src/Akela/Keyboard.cpp \
	../lib/Akela/src/Akela/KeyMap.cpp \
	../lib/Akela/src/Akela/LayeredKeyMap.cpp \
	../lib/Akela/src/Akela/EventHandler/Base.cpp \
	../lib/Akela/src/Akela/EventHandler/Components/Layer.cpp \
	../lib/Akela/src/Akela/EventHandler/Layered.cpp
AKELA_HEADERS = \
	${AKELA_SOURCES:.cpp=.h} \
	../lib/Akela/src/Akela.h \
	../lib/Akela/src/Akela/AbstractHID.h \
	../lib/Akela/src/Akela/KeyCodes.h \
	../lib/Akela/src/Akela/SysFn.h \
	../lib/Akela/src/Akela/AbstractScanner.h \
	../lib/Akela/src/Akela/EventHandler/Component.h

TEST_SOURCES = \
	AkelaTest.cpp \
	TestCase/Basics.cpp \
	TestCase/Mods.cpp \
	TestCase/Fn.cpp \
	TestCase/Layers.cpp

TEST_HEADERS = \
	stubs/HID/Printer.h \
	stubs/KeyMap/Printer.h \
  stubs/KeyMap/LayerPrinter.h \
	stubs/keymaps.h \
	stubs/Keyboard/Chorded.h \
	stubs/Keyboard/PressRelease.h \
	stubs/Keyboard/PressReleaseLayered.h \
	stubs/EventHandler/FnPrinter.h \
  stubs/Scanner/NoOp.h

AkelaTest: ${TEST_SOURCES} ${AKELA_SOURCES} ${AKELA_HEADERS} ${TEST_HEADERS}
	${CXX} ${CXXFLAGS} ${AKELA_SOURCES} AkelaTest.cpp -o $@

clean:
	rm -f AkelaTest test.out

.PHONY: all clean check
