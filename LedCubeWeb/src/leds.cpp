//
// Created by sjr on 3/31/24.
//

#include "leds.hpp"

CRGB leds[NUM_LEDS];

#define EIGHT_LAYER_PIN 8

void initLeds() {
    FastLED.addLeds<WS2812, EIGHT_LAYER_PIN, RGB>(leds, 512);
}



int address(int x, int y, int z) {

    if (x < 0 || x > 7) {
        return -1;
    }

    if (y < 0 || y > 7) {
        return -1;
    }

    if (z < 0 || z > 7) {
        return -1;
    }


    if (z % 2  == 0) {
        if (y % 2 == 0) {
            return z*64+y*8 + x;
        } else {
            return z*64+(y+1)*8 - x - 1;
        }
    } else {
        // I just guessed at this
        if (y % 2 == 0) {
            return z*64+ 64 - (y*8 + x) - 1;
        } else {
            return z*64+ (64 -((y+1)*8 - x - 1)) - 1;
        }
    }




}


int address(int x) {
    return address(x % 8, (x / 8) % 8, x / 64);
}
