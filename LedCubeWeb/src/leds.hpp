//
// Created by sjr on 3/31/24.
//

#ifndef LEDCUBEWEB_LEDS_HPP
#define LEDCUBEWEB_LEDS_HPP
#include "FastLED.h"
#define NUM_LEDS 512


void initLeds();

extern CRGB leds[NUM_LEDS];

int address(int x, int y, int z);

int address(int x);

#endif //LEDCUBEWEB_LEDS_HPP
