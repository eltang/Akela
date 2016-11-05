---
title: "High-level architecture"
permalink: /deep-dive/high-level-architecture/
excerpt: "High level architecture"
modified: 2016-11-05T21:25:00+01:00
---

{% include toc %}

In this guide, we will have a rough overview of the architecture, and the
motivations behind Akela. We will not dive deep into any part yet, we just lay
out the plan.

## Design decisions

When Akela started, the [Keyboardio Firmware][kbdio:fw] already existed, and had
a lot of functionality, and has been used on real hardware. Why start anew then?
A very good question. Originally, I did not start from scratch, but tried
various ways to extend the existing firmware with features I wished for. But
there was a big problem: the whole firmware was tightly coupled, adding new
features required one to touch the core of the firmware. My goal was - and still
is - to be able to add new functionality by *composing* libraries, extending
existing functionality, without having to touch their implementation.

 [kbdio:fw]: https://github.com/keyboardio/KeyboardioFirmware
 
Originally, I started with lifting out parts of `KeyboardioFirmware`, but soon
realised that to understand the inner workings better, and to have an API, and
architecture that meets my needs, it is easier to start from scratch.

Akela does reuse large parts of existing work, however: the `HID` and `Scanner`
parts of the Model 01 library are wrappers around [KeyboardioHID][kbdio:hid]
and [KeyboardioScanner][kbdio:scanner].

 [kbdio:hid]: https://github.com/keyboardio/KeyboardioHID
 [kbdio:scanner]: https://github.com/keyboardio/KeyboardioScanner
 
And so it began, that I started to design an API that I would consider useful.
It's not the most optimized one, nor the friendliest to newcomers, because the
goal was to make it composeable first. For that goal, the others had to be
sacrificed, at least to some extent.

## The libraries of Akela

As the goal from the very beginning was to make the thing a set of libraries one
can put together like a puzzle to form a firmware, Akela consists of a set of
libraries, too. Within these libraries, the various components are separated
too, as much as possible.

At the moment, there are three main parts:

* **The Core**: A hardware independent set of classes, that implement most of
  what I imagine a keyboard should be able to do. Obviously hardware-specific
  parts are left unimplemented.
  
* **The Model 01 library**: A set of classes on top of the Core, that tie
  together the KeyboardioHID, KeyboardioScanner with Akela, and implement
  features specific to the Model 01.
  
* **TapDance library**: One-shot modifiers and layers, and TapDance, implemented
  as a library outside of the core. This was made to prove the design is
  extendable, without having to patch and change the core too.

## The core library

The core library is in a strange situation: in itself, without another library
that ties it to some hardware, it is not too useful. Yet, without it, without
this foundation, the rest would not exist. The core library is the soul of the
whole, so to say.

Composed of smaller parts, the core library itself is not much more than a
collection of classes that can implement a keyboard. Lets start looking at the
bits and pieces from the highest level!

### The keyboard

At the top is the `Akela::Keyboard` class, a very simple component: with a
keyboard, one should be able to run some initialization code, have a main loop,
and methods to press, release and hold keys. For this to work, the keyboard will
have to access a `Scanner`, the part which scans the keys and reports their
state, and an `EventHandler` to take care of the events based on the scanners
results.

This is all the top-level Keyboard class does, really: tie the pieces together.
Pull input from the scanner, and present them to the event handler as a set of
events, forever and ever, until the keyboard is plugged in.

### Scanner

The scanner, described in `Akela::AbstractScanner` is another very simple
concept: it has a `setup` method like all the rest, for any initialization
purposes; and a `scan` method that returns... something. That something is
specific to each and every keyboard, and should describe the keys pressed that
cycle.

### Event Handler

The event handler is the most complex piece of the puzzle, and there are two
variants of it in the core library: one that only supports a single layer, and
one that supports as many as one can imagine (limited by hardware resources, of
course).

Its purpose is to handle all the events the keyboard presents it, and
ultimately - via the low-level HID component described a few paragraphs down -,
report the new things back to the host, or do whatever the programmer asked it
to do. Be that lighting up LEDs, or anything else.

It does not deal directly with the keymap, however: it receives just the index
of keys, and uses another component, the `keymap`, to look up a key code. It
then acts on the key code itself, or delegates the work to one of the pluggable
components.

We will have a closer look at the event handler later, and will touch upon the
components as well. For now, just imagine it as a piece of code that makes
decisions, and delegates the actual work to other components. The `Scanner`
feeds it, via the `Keyboard`; it uses the `Keymap` to translate indexes to
codes; decides on an action, and asks the `HID` (or a `Component`) to perform
the action decided upon.

### The key map

The key map is likely the simplest component in the whole library: its sole
purpose is to turn an index into a key code. The most basic variant just looks
up the index in an array, but a slightly more complex variant is also provided
in the library, that can also handle simplistic layers.

This is used by the `EventHandler`, and pretty much nothing else.

### Low-level HID

The lowest level, dumbest part (at least in some sense) of the lot: it receives
a keycode (a much simpler one than the `EventHandler`, mind you), and eventually
sends it to the host.

## Hardware libraries

Hardware libraries - only the `Model 01` library exists for now - fill the gap
between real hardware and the core library. These implement features specific to
the keyboard (such as LEDs on the Model 01). These wrap the hardware specific
scanner in a form that the core library can use it. It's the flesh on the
skeleton.

## Extras

There is currently only one extra library, the `TapDance` library, bringing
features independent of the hardware, that for one reason or another, were not
put into the core library. Mostly, these are non-essential things.

## What's next?

This was a very high level overview. Next time, we will look into each of the
classes, and see what talks to what, how, and why.
