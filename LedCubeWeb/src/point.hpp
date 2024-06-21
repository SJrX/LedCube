//
// Created by sjr on 3/31/24.
//

#ifndef LEDCUBEWEB_POINT_HPP
#define LEDCUBEWEB_POINT_HPP

#include "Arduino.h"
class Point {
public:
    int8_t x;
    int8_t y;
    int8_t z;
    Point() : x(0), y(0), z(0) {

    }

    Point(int8_t x, int8_t y, int8_t z): x(x), y(y), z(z) {

    }

    bool IsOutOfBounds() {
        return x < 0 || x >= 8 || y < 0 || y >= 8 || z < 0 || z >= 8;
    };
};


#endif //LEDCUBEWEB_POINT_HPP
