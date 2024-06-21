//
// Created by sjr on 3/31/24.
//

#ifndef LEDCUBEWEB_PARABOLIC_TRAJECTORY_HPP
#define LEDCUBEWEB_PARABOLIC_TRAJECTORY_HPP
#include "animations.hpp"

class ParabolicTrajectory : public Animation {
public:
    Point* p1;
    Point* p2;

    CRGB color;
    bool blend;
    Animation** nextArr;

    ParabolicTrajectory(int frames, Point* start, Point* end, CRGB Color, boolean blend, Animation** nextArr);
    void draw() override;
    bool done() override;
    ~ParabolicTrajectory();
    Animation** next() override;
};

#endif //LEDCUBEWEB_PARABOLIC_TRAJECTORY_HPP
