#include "constant.hpp"



#define CONSTANT_COLOR_MODES 3


void ConstantColor::Next() {
    Serial.println("Next");
    this->mode = (this->mode+1)  % CONSTANT_COLOR_MODES;
}

void ConstantColor::Prev() {
    Serial.println("Prev");
    // I'm too lazy to check how mod works with negative numbers.
    this->mode = (this->mode + (CONSTANT_COLOR_MODES - 1)) % CONSTANT_COLOR_MODES;
}

void ConstantColor::Up() {

    this->modes[this->mode]->Up();

}

void ConstantColor::Down() {
    this->modes[this->mode]->Down();
}

void ConstantColor::Number(int val) {
    this->modes[this->mode]->Number(val);
}

void ConstantColor::DrawNextFrame(unsigned long frameCount) {
    int val = ((this->red * 32) << 16) + ((this->green * 32) << 8) + this->blue * 32;
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(val);
    }

    Serial.print("Color:" );
    Serial.print(this->red);
    Serial.print(",");
    Serial.print(this->blue);
    Serial.print(",");
    Serial.print(this->green);
    Serial.print(": ");
    Serial.println(val);
}
