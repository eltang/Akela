---
title: "Building your own layout"
permalink: /guide/building-your-own-layout/
excerpt: "How to build a custom layout from scratch?"
modified: 2016-11-04T14:00:00+01:00
---

{% include toc %}

If you have not read the [getting started](/getting-started/) guide yet, please
do so, this guide builds on the assumption that we have everything installed and
set up, and that we can compile the examples included with the library.

Building the included examples is all good and useful, but one of the lucrative
features of a fully programmable keyboard is to customize the firmware. In this
guide, we will have a brief look at how to do the first steps in customisation:
changing the layout. We will only use the basics only: no macros, LED effects,
or anything fancier that can be expressed within the keymap layout itself. We
will not be writing any code, just changing some data, really. Trust me, it is
less complicated than it sounds!

## Starting a new Sketch

For educational purposes, we will start from scratch. We can use either the
command-line, or the [Arduino IDE][arduino:ide]. The two should not be mixed,
though.

[arduino:ide]: https://www.arduino.cc/en/Main/Software

### From the command line

We can use the `user/new-sketch` tool to start with a complete, but not very
functional base:

```
$ user/new-sketch my-own-layout
```

We can immediately compile it from the command-line with the `make
user/my-own-layout` command, and the result will be under the `firmware/user/`
directory. For convenience, the system always creates a symbolic link to the
latest version. In this case, this will be
`firmware/user/my-own-layout-latest.hex`.

This can be flashed onto the keyboard, but it will not do anything useful yet,
because the layout is completely empty.

### From the Arduino IDE

With the [Arduino IDE][arduino:ide], we can find the template in the
`File/Examples` menu, in an `Akela-User` submenu. Load the example, and save it
to your Sketchbook. Compiling and uploading the firmware from the IDE can be
done as usual.

## Editing the layout

The new sketch is made up of two files: `my-own-layout.ino`, and `layout.h`. In
this guide, we will only touch the latter. The former is the heart of the
firmware, that sets up the various bits and pieces that make up a keyboard
controller, and ties them together. One part of these is the layout of the keys,
and that is what we will be editing in `layout.h`!

<figure>
  <img src="{{ '/assets/images/guides/building-your-own-layout/arduino-ide-layout.h.png' | absolute_url }}" 
       alt="Editing layout.h with the Arduino IDE">
</figure>

As you can see, all the keycodes are `KC_NO`, short for *do nothing*. We will go
ahead and turn it into something useful, like a simple QWERTY layout.

### Adding alphanumerics

As a first step, we will add the alpha and numeric keys. Not very useful on
their own, without the likes of `Enter` or the modifiers, but its a start,
right? With the `layout.h` file open, replace the keymap declaration with this:

```c++
static const uint16_t keymap[][64] PROGMEM = {
 [BASE] = KEYMAP (
 // left hand

  KC_NO     ,KC_1      ,KC_2      ,KC_3      ,KC_4      ,KC_5      ,KC_NO
 ,KC_NO     ,KC_Q      ,KC_W      ,KC_E      ,KC_R      ,KC_T 
 ,KC_NO     ,KC_A      ,KC_S      ,KC_D      ,KC_F      ,KC_G      ,KC_NO
 ,KC_NO     ,KC_Z      ,KC_X      ,KC_C      ,KC_V      ,KC_B      ,KC_NO

                 ,KC_NO     ,KC_NO     ,KC_NO     ,KC_NO
                            ,KC_NO

  // right hand

  ,KC_NO     ,KC_6      ,KC_7      ,KC_8      ,KC_9      ,KC_0      ,KC_NO
             ,KC_Y      ,KC_U      ,KC_I      ,KC_O      ,KC_P      ,KC_NO
  ,KC_NO     ,KC_H      ,KC_J      ,KC_K      ,KC_L      ,KC_NO     ,KC_NO
  ,KC_NO     ,KC_N      ,KC_M      ,KC_NO     ,KC_NO     ,KC_NO     ,KC_NO

                 ,KC_NO    ,KC_NO      ,KC_NO     ,KC_NO
                           ,KC_NO
 ),
};
```

So far so good, and straightforward, too! As you can see, each symbol is
prefixed with `KC_`, and is in uppercase. So the `a` and `A` symbols are
represented by `KC_A`. To get an uppercase `A`, we will need a `Shift` key. Lets
add those!

### Shifting the world, one key at a time

There are two `Shift` keys: the left and the right one. We will put them on the
thumb cluster, the inner keys on both sides. As such, our layout changes to the
following:

```c++
static const uint16_t keymap[][64] PROGMEM = {
 [BASE] = KEYMAP (
 // left hand

  KC_NO     ,KC_1      ,KC_2      ,KC_3      ,KC_4      ,KC_5      ,KC_NO
 ,KC_NO     ,KC_Q      ,KC_W      ,KC_E      ,KC_R      ,KC_T 
 ,KC_NO     ,KC_A      ,KC_S      ,KC_D      ,KC_F      ,KC_G      ,KC_NO
 ,KC_NO     ,KC_Z      ,KC_X      ,KC_C      ,KC_V      ,KC_B      ,KC_NO

                 ,KC_NO     ,KC_NO     ,KC_NO     ,KC_LSFT
                            ,KC_NO

  // right hand

  ,KC_NO     ,KC_6      ,KC_7      ,KC_8      ,KC_9      ,KC_0      ,KC_NO
             ,KC_Y      ,KC_U      ,KC_I      ,KC_O      ,KC_P      ,KC_NO
  ,KC_NO     ,KC_H      ,KC_J      ,KC_K      ,KC_L      ,KC_NO     ,KC_NO
  ,KC_NO     ,KC_N      ,KC_M      ,KC_NO     ,KC_NO     ,KC_NO     ,KC_NO

                 ,KC_RSFT   ,KC_NO     ,KC_NO     ,KC_NO
                            ,KC_NO
 ),
};
```

We are using a shorter name for both shifts, so the layout description does not
become too wide. Still, they also start with `KC_`: this is true for all normal
key codes, all of them start with `KC_`. There are other things we can put in a
keymap like this, and we'll get to those soon enough.

### Enter, space, and punctuation

But first, lets make the keyboard marginally useful, by adding an `Enter`,
`Space`, `Backspace`, and some punctuation keys:

```c++
static const uint16_t keymap[][64] PROGMEM = {
 [BASE] = KEYMAP (
 // left hand

  KC_NO     ,KC_1       ,KC_2       ,KC_3       ,KC_4       ,KC_5       ,KC_NO
 ,KC_GRV    ,KC_Q       ,KC_W       ,KC_E       ,KC_R       ,KC_T 
 ,KC_NO     ,KC_A       ,KC_S       ,KC_D       ,KC_F       ,KC_G       ,KC_NO
 ,KC_NO     ,KC_Z       ,KC_X       ,KC_C       ,KC_V       ,KC_B       ,KC_NO

                 ,KC_NO     ,KC_BSPC   ,KC_NO     ,KC_LSFT
                            ,KC_NO

  // right hand

  ,KC_NO     ,KC_6      ,KC_7      ,KC_8      ,KC_9      ,KC_0      ,KC_NO
             ,KC_Y      ,KC_U      ,KC_I      ,KC_O      ,KC_P      ,KC_EQL
  ,KC_ENT    ,KC_H      ,KC_J      ,KC_K      ,KC_L      ,KC_SCLN   ,KC_QUOT
  ,KC_NO     ,KC_N      ,KC_M      ,KC_COMM   ,KC_DOT    ,KC_SLSH   ,KC_MINS

                 ,KC_RSFT   ,KC_NO     ,KC_SPC    ,KC_NO
                            ,KC_NO
 ),
};
```

We have `KC_GRV` for `~` and the backtick, on the first column in the second row
of the left side. We also have `KC_BSPC` for `Backspace` on the left thumb
cluster. The right side has seen more updates: `KC_EQL` on the far right in the
second row, for `=` and `+`; `KC_ENT` for `Enter` on the inner edge of the third
row; `KC_SCLN` (short for *semi-colon*) for `;` and `:`, just to the right of
the `L` key; and `KC_QUOT` for the *apostrophe* and the *quotation mark* beside
it. We also have `KC_COMM` for the *comma* and the *less-than sign*; `KC_DOT`
for the *dot* and the *greater-than sign*; and `KC_MINS` for *minus* and
*underscore*, at the right side of the keyboard. Our space is on the right thumb
cluster, going under the `KC_SPC` code.

Nothing out of the extraordinary so far, yes? The keycode names can be a bit
cryptic, indeed. For now, please consult the [KeyCodes.h][src:keycodes.h] file
in the sources, would any of them fail to make sense.

 [src:keycodes.h]: https://github.com/algernon/Akela/blob/master/lib/Akela/src/Akela/KeyCodes.h
 
### Control, Alt, and other modifiers

This is almost usable now. We do need some modifiers, so that we can have nice
shortcuts. Lets put the two `Control` keys on the outer side of the thumb
cluster, and the two `Alt` keys beside the `Shift` keys.

```c++
static const uint16_t keymap[][64] PROGMEM = {
 [BASE] = KEYMAP (
 // left hand

  KC_NO     ,KC_1       ,KC_2       ,KC_3       ,KC_4       ,KC_5       ,KC_NO
 ,KC_GRV    ,KC_Q       ,KC_W       ,KC_E       ,KC_R       ,KC_T 
 ,KC_NO     ,KC_A       ,KC_S       ,KC_D       ,KC_F       ,KC_G       ,KC_NO
 ,KC_NO     ,KC_Z       ,KC_X       ,KC_C       ,KC_V       ,KC_B       ,KC_NO

                 ,KC_LCTL   ,KC_BSPC   ,KC_LALT   ,KC_LSFT
                            ,KC_NO

  // right hand

  ,KC_NO     ,KC_6      ,KC_7      ,KC_8      ,KC_9      ,KC_0      ,KC_NO
             ,KC_Y      ,KC_U      ,KC_I      ,KC_O      ,KC_P      ,KC_EQL
  ,KC_ENT    ,KC_H      ,KC_J      ,KC_K      ,KC_L      ,KC_SCLN   ,KC_QUOT
  ,KC_NO     ,KC_N      ,KC_M      ,KC_COMM   ,KC_DOT    ,KC_SLSH   ,KC_MINS

                 ,KC_RSFT   ,KC_RALT   ,KC_SPC    ,KC_RCTL
                            ,KC_NO
 ),
};
```

That was easy. What are we still missing?

### ESC, Tab, and the GUI key

Right, `Esc`, `Tab`, and the `GUI` key. The former two could have a nice place
on the inner side of the left half. The `GUI` key? Lets put that onto the
butterfly key under `Enter`, at least for now. We can always come back and
rearrange the layout if we dislike it.

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

We still have a number of empty keys, and a few symbols (like brackets) we could
put on the keymap. Where to put them, is left as an exercise for the reader.
Find a place for them, put them there, and try it!

With the above layout, we have a keyboard we can use to input text, and control
the computer to some extent, and it will be the basis of the next few tutorials.
Stay tuned!

<figure>
  <img src="{{ '/assets/images/guides/building-your-own-layout/arduino-ide-layout.h-finished.png' | absolute_url }}" 
       alt="The finished layout.h in the Arduino IDE">
</figure>
