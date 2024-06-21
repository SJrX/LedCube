//
// Created by sjr on 3/31/24.
//

#ifndef LEDCUBEWEB_ANIMATIONS_HPP
#define LEDCUBEWEB_ANIMATIONS_HPP

#include "../point.hpp"
#include "../drawing.hpp"

class Animation {
public:
    Animation(int frames);
    int currentFrame = 0;

    int totalFrames;
    // Pure virtual function
    virtual void draw() = 0;

    virtual bool done() = 0;

    virtual ~Animation() {};
    virtual Animation** next() = 0;


};


#endif //LEDCUBEWEB_ANIMATIONS_HPP
