//
// Created by sjr on 3/31/24.
//
#include "moving_point.hpp"

Animation** MovingPoint::next() {
    return 0;
}


MovingPoint::MovingPoint(int frames, Point* start, Point* end, CRGB color, boolean blend) : Animation(frames)  {
    this->p1 = start;
    this->p2 = end;
    this->color = color;
    this->blend = blend;

}

bool MovingPoint::done() {
    return this->currentFrame == this->totalFrames;
}

MovingPoint::~MovingPoint() {
    delete p1;
    delete p2;
}




void MovingPoint::draw() {
    int dx = p2->x - p1->x;
    int dy = p2->y - p1->y;
    int dz = p2->z - p1->z;

    //int steps = max(abs(dx), max(abs(dy), abs(dz))); // Maximum difference determines the steps
    int steps = this->totalFrames;

    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;
    float zIncrement = dz / (float) steps;

    float x = p1->x;
    float y = p1->y;
    float z = p1->z;

    int currentStep = this->currentFrame;
    // Serial.println("Current frame");
    // Serial.print(currentStep);

    //for (int i = 0; i <= steps; i++) {
    // Printing the current point

    x += xIncrement*currentStep;
    y += yIncrement*currentStep;
    z += zIncrement*currentStep;


    int cX = int(round(x));
    int cY = int(round(y));
    int cZ = int(round(z));

    if (blend) {
        drawPoint(x, y, z, this->color);
    } else {
        drawPoint(cX, cY, cZ, this->color);
    }



    this->currentFrame++;
}


