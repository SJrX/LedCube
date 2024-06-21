#include "rgb.hpp"




void Rgb::Next() {
    Serial.println("Next");
    this->mode = (this->mode+1)  % RGB_MODES;
}

void Rgb::Prev() {
    Serial.println("Prev");
    // I'm too lazy to check how mod works with negative numbers.
    this->mode = (this->mode + (RGB_MODES - 1)) % RGB_MODES;
}

void Rgb::Up() {

    this->modes[this->mode]->Up();

}

void Rgb::Down() {
    this->modes[this->mode]->Down();
}

void Rgb::Number(int val) {
    this->modes[this->mode]->Number(val);
}




void Rgb::DrawNextFrame(unsigned long frameCount) {

    if (this->frequency > 0) {
        if ( (frameCount % this->frequency) == 0) {
            Serial.print("Frame:");
            Serial.println(frameCount);

            switch (random(3)) {
                case 0:
                    this->red = (this->red + this->delta) % 128;
                    break;
                case 1:
                    this->green = (this->green + this->delta) % 128;
                    break;
                case 2:
                    this->green = (this->green + this->delta) % 128;
                    break;
            }
            Serial.print("Color: 0x" );
            Serial.print(this->red*4, HEX);
            Serial.print(this->green*4, HEX);
            Serial.print(this->blue*4, HEX);
            Serial.println("");

        }
    }

    int val = ((this->red * 2) << 16) + ((this->green * 2) << 8) + this->blue * 2;


    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(val);
    }
}
