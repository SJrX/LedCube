#include "wavey.hpp"


void Wavey::Next() {
    Serial.println("Next");
    this->mode = (this->mode+1)  % WAVEY_MODES;
}

void Wavey::Prev() {
    Serial.println("Prev");
    // I'm too lazy to check how mod works with negative numbers.
    this->mode = (this->mode + (WAVEY_MODES - 1)) % WAVEY_MODES;
}

void Wavey::Up() {

    this->modes[this->mode]->Up();

}

void Wavey::Down() {
    this->modes[this->mode]->Down();
}

void Wavey::Number(int val) {
    this->modes[this->mode]->Number(val);
}


uint32_t colorForLevel(float level) {
    float ratio = level / 7.0;
    uint8_t red = (1 - ratio) * 255;
    uint8_t blue = ratio * 255;
    // Assuming an RGB LED setup, where color is represented as 0xRRGGBB
    return (red << 16) | (blue) | 0x000000; // No green component, red and blue are mixed based on level
}

uint32_t roygbvColorForLevel(float level) {
    float segmentLength = 7.0 / 5; // 5 transitions within the 0-7 range
    int segment = level / segmentLength; // Determines which segment we're in
    float ratio = (level - (segment * segmentLength)) / segmentLength; // Progress within segment

    // Initialize RGB components
    uint8_t red = 0, green = 0, blue = 0;

    // Calculate the color based on the segment
    switch (segment) {
        case 0: // Red to Orange
            red = 255;
            green = ratio * 255;
            break;
        case 1: // Orange to Yellow
            red = 255;
            green = 255;
            break;
        case 2: // Yellow to Green
            red = (1 - ratio) * 255;
            green = 255;
            break;
        case 3: // Green to Blue
            green = 255;
            blue = ratio * 255;
            break;
        case 4: // Blue to Violet
            red = ratio * 75; // Adding some red to get violet
            green = (1 - ratio) * 255;
            blue = 255;
            break;
        default: // Just in case
            red = 255;
            break;
    }

    // Assuming an RGB LED setup, where color is represented as 0xRRGGBB
    return (red << 16) | (green << 8) | blue;
}


void Wavey::DrawNextFrame(unsigned long frameCount) {

    for (int x = 0; x < 8; x++) {
        float phaseShift = this->frames++ * 0.0125;


        for (int y = 0; y < 8; y++) {

            float wavePositionX = sin(this->A*x * PI / 4 + (phaseShift + this->B)/this->W);
            float wavePositionY = sin(this->C*y * PI / 4 + phaseShift + this->D/this->W);

            // // Example combination: average of X and Y wave positions, scaled to fit 0-7 for z position
            float wavePosition = (wavePositionX + wavePositionY) / 2;

            wavePosition = (wavePosition+1)*3.5;



            // // Calculate distance from the center of the cube on the xy plane
            // float distanceFromCenter = sqrt(pow(x - 3.5, 2) + pow(y - 3.5, 2));

            // // Modulate the wave amplitude based on distance from center, peaking at the center
            // float amplitude = 4 - distanceFromCenter; // Max amplitude at the center, decreasing towards the edges

            // // Calculate a combined z position based on amplitude and phase shift
            // float wavePosition = sin(phaseShift)/2 * amplitude + 3.5; // Center goes up and down


            //float wavePosition = (sin(x * 4 * PI / 32 + phaseShift)*sin(y * 4 * PI / 32 + phaseShift)) * 4 + 1.75; // Scaled and shifted to fit 0-7


            //float wavePosition = (sin(x * 2 * PI / 32 + phaseShift) + 1) * 3.5; // Scaled and shifted to fit 0-7
            //float wavePosition = (sin(x * 2 * PI / 32 + phaseShift) + 1) * 3.75; // Scaled and shifted to fit 0-7
            if (wavePosition < 0) {
                wavePosition = 0.0;
            } else if (wavePosition > 7) {
                wavePosition = 7.0;
            }
            int z = round(wavePosition);


            int i = address(x,y,z);
            if (i > 0 && i < 512) {
                //leds[i] = colorForLevel(z);

                drawPoint((float) x, (float) y, (float) wavePosition, roygbvColorForLevel(wavePosition));
            }
        }
    }

}
