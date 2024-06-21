//
// Created by sjr on 3/31/24.
//

#ifndef LEDCUBEWEB_DRAWING_HPP
#define LEDCUBEWEB_DRAWING_HPP
#include "FastLED.h"
#include "leds.hpp"

void drawLine(int x1, int y1, int z1, int x2, int y2, int z2, CRGB color);

void drawBox(int x0, int y0, int z0, int x1, int y1, int z1, CRGB color);

void clearLayers(int minLayer, int maxLayer);

void drawPoint(float x, float y, float z, CRGB color);

void drawPoint(int x, int y, int z, CRGB color);
#endif //LEDCUBEWEB_DRAWING_HPP
