# nRF52-PlayOpus - Play an Opus Audio File with an nRF52!
Current Status: In development, not working yet.

## Brief
The purpose of this library is to get an nRF52 to play an Opus audio file over I2S to an amplifier.  This should be done with the minimal amount of complexity.

## Why?
I haven't found a good implementation of this for nRF52's.  There's stuff for Teensy's and ESP's, but the only thing I've found for nRF's is the example code from Nordic for some smart remote thing.  Problem is, the smart remote implementation is for encoding only.  Nordic does, however, provide an optimized decoder here.

The implementations that do exist are overly complicated in my opinion.  Especially with regards to Ogg file parsing, this parser will just strip out the fancy file chunking stuff and throw it straight to the decoder.

## IDE/Compiler Setup
I'm using PlatformIO for this.  Adafruit provides a lot of the groundwork here that I plan to use for prototyping.  Eventually, I'm going to make this a cleaner, more general library.

I do plan to write it in pure C, versus the Arduino-style convention that PlatformIO likes.  Primary reason for this is I plan to use this in a non-Arduino setup later on, and just prefer C to Arduino's basic-ified C++.

## Current Hardware Setup
Currently, I'm developing this using an Adafruit nRF52840-Sense board available at: https://www.adafruit.com/product/4516
This is plugged into a MAX98357A I2S amplifier board, also from Adafruit at: https://www.adafruit.com/product/3006
