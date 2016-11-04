// -*- mode: c++ -*-

#include <Akela.h>
#include <Akela-Model01.h>

#include "layout.h"

static M01::HID::Full          hid;
static M01::KeyMap             keyMap (keymap);
static M01::Scanner            scanner;
static M01::EventHandler::Full eventHandler (&hid, &keyMap, &scanner);
static M01::Model01            keyboard (&scanner, &eventHandler);

void
setup () {
  keyboard.setup ();
}

void
loop () {
  keyboard.loop ();
}
