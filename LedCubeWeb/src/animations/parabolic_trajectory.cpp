//
// Created by sjr on 3/31/24.
//

#include "parabolic_trajectory.hpp"

bool ParabolicTrajectory::done() {
    return this->currentFrame == this->totalFrames;
}

Animation** ParabolicTrajectory::next() {
    return 0;
}

ParabolicTrajectory::ParabolicTrajectory(int frames, Point* start, Point* end, CRGB color, boolean blend, Animation** nextArr) : Animation(frames)  {
    this->p1 = start;
    this->p2 = end;

    this->color = color;
    this->blend = blend;
    this->nextArr = nextArr;

}

ParabolicTrajectory::~ParabolicTrajectory() {
    delete p1;
    delete p2;
}

#define GRAVITY 0.00075

void ParabolicTrajectory::draw() {
    int dx = p2->x - p1->x;
    int dy = p2->y - p1->y;


    int steps = this->totalFrames;

    int currentStep = this->currentFrame;

    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;


    float initialZSpeed = (p2->z + 0.5*GRAVITY*steps*steps - p1->z)/steps;



    float z = -0.5*GRAVITY*currentStep*currentStep + initialZSpeed * currentStep + p1->z;

    // float zIncrement = dz / (float) steps;

    float x = p1->x;
    float y = p1->y;


    x += xIncrement*currentStep;
    y += yIncrement*currentStep;


    int cX = int(round(x));
    int cY = int(round(y));
    int cZ = int(round(z));

    // Serial.print("(");
    // Serial.print(x);
    // Serial.print(",");
    // Serial.print(y);
    // Serial.print(")=>");
    // Serial.print(z);

    // Serial.println("");

    if (blend) {
        drawPoint(x, y, z, this->color);
    } else {
        drawPoint(cX, cY, cZ, this->color);
    }


    this->currentFrame++;
}

