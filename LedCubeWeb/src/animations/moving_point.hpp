//
// Created by sjr on 3/31/24.
//

#ifndef LEDCUBEWEB_MOVING_POINT_HPP
#define LEDCUBEWEB_MOVING_POINT_HPP
#include <Arduino.h>
#include "animations.hpp"
#include "FastLED.h"

class MovingPoint : public Animation {
public:
    Point* p1;
    Point* p2;
    CRGB color;
    bool blend;

    MovingPoint(int frames, Point* start, Point* end, CRGB Color, boolean blend);
    void draw() override;
    bool done() override;
    ~MovingPoint();
    Animation** next() override;



};

#endif //LEDCUBEWEB_MOVING_POINT_HPP
