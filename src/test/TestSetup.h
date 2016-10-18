#include "Akela.h"

#ifndef ARDUINO
# include <iostream>
# include <iomanip>
#endif

static uint16_t TestLayout[][64] = {
  [0] = {
   KC_F11   ,KC_9     ,KC_7     ,KC_5     ,KC_3     ,KC_1     ,KC_NO
  ,KC_BSLS  ,KC_X     ,KC_W     ,KC_C     ,KC_H     ,KC_F
  ,KC_TAB   ,KC_A     ,KC_O     ,KC_E     ,KC_I     ,KC_U     ,LSFT(KC_9)
  ,KC_MPLY  ,KC_Z     ,KC_Q     ,KC_QUOT  ,KC_COMM  ,KC_DOT   ,KC_NO

                                            ,KC_NO    ,KC_BSPC  ,KC_NO    ,KC_NO
                                                          ,KC_NO


                                                    ,KC_NO    ,KC_0     ,KC_2     ,KC_4     ,KC_6     ,KC_8     ,KC_NO
                                                              ,KC_M     ,KC_G     ,KC_L     ,KC_P     ,KC_SLSH  ,KC_GRV
                                                    ,KC_NO    ,KC_D     ,KC_R     ,KC_T     ,KC_N     ,KC_S     ,KC_EQL
                                                    ,KC_NO    ,KC_B     ,KC_K     ,KC_V     ,KC_Y     ,KC_J     ,KC_MSTP

                                            ,KC_NO    ,KC_SPC   ,KC_ENT   ,KC_MINS
                                                          ,KC_NO
  },
  [1] = {
   KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
  ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
  ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
  ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO

                                            ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                          ,KC_NO


                                                    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                              ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO

                                            ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                          ,KC_NO

  }
  };

//

class TestKeyMap : public AkelaKeyMap {
 public:
  TestKeyMap (uint16_t *keymap) : AkelaKeyMap (keymap) {};

  virtual uint16_t lookup (uint8_t index) {
    uint16_t k = AkelaKeyMap::lookup (index);
#ifndef ARDUINO
    std::cout << __PRETTY_FUNCTION__ << "(" << (int)0 << ", "
              << (int)index << ") = " << std::hex << (int)k << std::endl;
#endif
    return k;
  }
};

//

class MyKeyboard : public AkelaKeyboard {
protected:
  virtual void cycle () {
    press (19);
  };

public:
  MyKeyboard (AkelaKeyEventHandler *eh, AkelaKeyMap *keymap) : AkelaKeyboard (eh, keymap) {
  };
};

//

class TestHID : public virtual AkelaAbstractHID {
 public:
  virtual void press (uint8_t code) {
#ifndef ARDUINO
    std::cout << __PRETTY_FUNCTION__ << "(0x" << std::hex << (int)code << ")" << std::endl;
#endif
  };

  virtual void release (uint8_t code) {
#ifndef ARDUINO
    std::cout << __PRETTY_FUNCTION__ << "(0x" << std::hex << (int)code << ")" << std::endl;
#endif
  };

  TestHID () : AkelaAbstractHID () {};
};

// -------------------------------------------------------------------------------------

static TestHID MyHID = TestHID ();
static AkelaKeyEventHandler TestEH = AkelaKeyEventHandler (&MyHID);
static TestKeyMap MyKeyMap = TestKeyMap ((uint16_t *)TestLayout);
MyKeyboard keyboard = MyKeyboard (&TestEH, &MyKeyMap);
