//
// Created by sjr on 4/1/24.
//
#include "matrix_manager.hpp"

#define DISPLAY_TIMEOUT_MILLIS 2000

void MatrixManager::init() {
    this->disp = new simpleMatrix(4, 1);
    this->disp->begin();
    // Set the LED's intensity. This value can be anywhere between 0 and 15.
    this->disp->setIntensity(0x1);

}


void MatrixManager::SetIcon(uint8_t icon) {

    if (this->lastIcon != icon) {
        this->lastIcon = icon;
        this->lastDisplayTime = millis();
        char myString[2];
        myString[0] = icon;
        myString[1] = '\0';
        this->disp->print(myString, 1);
    } else if ((millis() - this->lastDisplayTime) > DISPLAY_TIMEOUT_MILLIS) {
        this->disp->clearDisplay();
        this->lastDisplayTime = 0;
    }

}

MatrixManager mm = MatrixManager();