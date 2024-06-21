//
// Created by sjr on 3/31/24.
//

#ifndef LEDCUBEWEB_PROGRAMS_HPP
#define LEDCUBEWEB_PROGRAMS_HPP
#include "Arduino.h"
#include "remote_controlled_int.hpp"
#include "../point.hpp"
#include "../leds.hpp"
#include "../animations/animations.hpp"
#include "../animations/moving_point.hpp"
#include "../animations/parabolic_trajectory.hpp"

class Program {
public:
    Program() = default;
    virtual int NextFrame() final;

    virtual void VolUp() { };
    virtual void VolDown() { };
    virtual void Up() { };
    virtual void Down() { };
    virtual void Number(int val) { };
    virtual void Next() { };
    virtual void Prev() { };
    virtual void Eq() { };
    virtual void Play() { };
    virtual uint8_t Icon() = 0;
protected:
    virtual void DrawNextFrame(unsigned long frameCounter) = 0;

private:
    unsigned long frameCounter = 0;
    //virtual CRGB ModeColor() { CRGB::Black; }
};

#endif //LEDCUBEWEB_PROGRAMS_HPP
