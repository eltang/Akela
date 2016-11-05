---
title: "One shot in the dark"
permalink: /guide/one-shot-in-the-dark/
excerpt: "The purpose and use of one-shot modifiers"
modified: 2016-11-05T14:00:00+01:00
---

{% include toc %}

Continuing where we left off [last time](/building-your-own-layout/), we will
have a look at some of the more advanced features of the library: One-shot
modifiers. We will see what they can be used for, and how to put them on our
layout.

## A brief tour of one-shot modifiers

As their name implies, *one-shot modifiers* expire after their only shot, but
they make that one count. Unlike the traditional modifiers which we have to hold
down to keep them active, one-shots remain active, even when released, until
after another key is pressed, that is not a similar one-shot key. They also have
a second feature, where you can double-tap them, and keep them active until a
third tap.

One may wonder why the behaviour described above is useful, or even needed.
Wonder no more, for this guide right here, will explain it clearly!

### The problems one-shot modifiers solve

Do you remember where we put the modifiers last time? On the thumb cluster. Why?
Because we did not have enough room elsewhere, to put them to their traditional
places, for one. But that's just a secondary reason. The real reason we didn't
even know we had, is that holding modifiers with our weakest digits is not good
for the health of our hands. In an age where we use lots of key combos daily,
most of them involving the modifiers, having the modifiers under weaker digits
is hazardous. So we put them under the thumbs. Yet, that means weird finger
gymnastics when trying to hold some combinations like `Ctrl + Shift + Q`. We do
not have two thumbs on each hand, so how do we even input this?

One-shot modifiers are the answer: tap them, release them, and press another
key. Combos, chords become sequences, which require much less force - because we
do not need to hold any keys! -, and allow us to place modifiers to places that
would otherwise be impossible if we relied on chording. Instead of `Ctrl +
Shift + Q`, we'd use `Ctrl, Shift, Q`: same keys, same order, but tapped in
sequence, not held together.

## Changing modifiers to be one-shot

As a reminder, this is how our layout looked when we took a short break:

```c++
static const uint16_t keymap[][64] PROGMEM = {
 [BASE] = KEYMAP (
 // left hand

  KC_NO     ,KC_1       ,KC_2       ,KC_3       ,KC_4       ,KC_5       ,KC_NO
 ,KC_GRV    ,KC_Q       ,KC_W       ,KC_E       ,KC_R       ,KC_T 
 ,KC_NO     ,KC_A       ,KC_S       ,KC_D       ,KC_F       ,KC_G       ,KC_TAB
 ,KC_NO     ,KC_Z       ,KC_X       ,KC_C       ,KC_V       ,KC_B       ,KC_ESC

                 ,KC_LCTL   ,KC_BSPC   ,KC_LALT   ,KC_LSFT
                            ,KC_NO

  // right hand

  ,KC_NO     ,KC_6      ,KC_7      ,KC_8      ,KC_9      ,KC_0      ,KC_NO
             ,KC_Y      ,KC_U      ,KC_I      ,KC_O      ,KC_P      ,KC_EQL
  ,KC_ENT    ,KC_H      ,KC_J      ,KC_K      ,KC_L      ,KC_SCLN   ,KC_QUOT
  ,KC_LGUI   ,KC_N      ,KC_M      ,KC_COMM   ,KC_DOT    ,KC_SLSH   ,KC_MINS

                 ,KC_RSFT   ,KC_RALT   ,KC_SPC    ,KC_RCTL
                            ,KC_NO
 ),
};
```

Compare that to the following, which turns all modifiers on the thumb cluster
into one-shots! Can you spot the difference?

```c++
static const uint16_t keymap[][64] PROGMEM = {
 [BASE] = KEYMAP (
 // left hand

  KC_NO     ,KC_1       ,KC_2       ,KC_3       ,KC_4       ,KC_5       ,KC_NO
 ,KC_GRV    ,KC_Q       ,KC_W       ,KC_E       ,KC_R       ,KC_T 
 ,KC_NO     ,KC_A       ,KC_S       ,KC_D       ,KC_F       ,KC_G       ,KC_TAB
 ,KC_NO     ,KC_Z       ,KC_X       ,KC_C       ,KC_V       ,KC_B       ,KC_ESC

                 ,OSM(KC_LCTL) ,KC_BSPC      ,OSM(KC_LALT) ,OSM(KC_LSFT)
                               ,KC_NO

  // right hand

  ,KC_NO     ,KC_6      ,KC_7      ,KC_8      ,KC_9      ,KC_0      ,KC_NO
             ,KC_Y      ,KC_U      ,KC_I      ,KC_O      ,KC_P      ,KC_EQL
  ,KC_ENT    ,KC_H      ,KC_J      ,KC_K      ,KC_L      ,KC_SCLN   ,KC_QUOT
  ,KC_LGUI   ,KC_N      ,KC_M      ,KC_COMM   ,KC_DOT    ,KC_SLSH   ,KC_MINS

                 ,OSM(KC_RSFT) ,OSM(KC_RALT) ,KC_SPC    ,OSM(KC_RCTL)
                            ,KC_NO
 ),
};
```

Yes, it was that easy. Wrapping any modifier within an `OSM()` - short for
**o**ne-**s**hot **m**odifier - makes them one-shot, and sport the behaviour
described above.

With this short introduction, we learned about one of the easiest functions
available for our keymaps. There are a number of others, and we will touch upon
them in the next guides! For now, go ahead and try the one-shot modifiers, see
if they work for you!
