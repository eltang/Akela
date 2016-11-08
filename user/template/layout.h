// -*- mode: c++ -*-

#pragma once

// Layers
enum {
  BASE,
};

// The keymap itself
static const uint16_t keymap[][64] PROGMEM = {
  /* Base layout
   *
   * ,-----------------------------------------.                    ,-----------------------------------------.
   * |     |     |     |     |     |     |     |                    |     |     |     |     |     |     |     |
   * |-----+-----+-----+-----+-----+-----|     |                    |     |-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |-----|                    |-----|     |     |     |     |     |     |
   * |-----+-----+-----+-----+-----+-----|     |                    |     |-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     |                    |     |     |     |     |     |     |     |
   * |-----+-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     |                    |     |     |     |     |     |     |     |
   * `-----+-----+-----+-----+-----+-----------'                    `-----------+-----+-----+-----+-----+-----'
   *
   *                            ,-----.                                      ,-----.
   *                            |     |-----.                          ,-----|     |
   *                            `-----|     |-----.              ,-----|     |-----'
   *                                  `-----|     |-----.  ,-----|     |-----'
   *                                        `-----|     |  |     |-----'
   *                                              `-----'  `-----'
   *                                  ,-------.                      ,-------.
   *                                  |       |                      |       |
   *                                  |       |                      |       |
   *                                  `-------'                      `-------'
   *
   */
  [BASE] = KEYMAP (
  // left hand

   KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO
  ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO
  ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO
  ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO

                   ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO
                               ,KC_NO

   // right hand

   ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO
   ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO
               ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO
   ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO

                   ,KC_NO      ,KC_NO      ,KC_NO      ,KC_NO
                               ,KC_NO
  ),
};
