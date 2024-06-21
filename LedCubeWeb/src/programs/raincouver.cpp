#include "raincouver.hpp"

#include "animations/animations_manager.hpp"

void Raincouver::Next() {
    // Serial.print("Next:");
    this->mode = (this->mode + 1) % RAINCOUVER_MODES;
    // Serial.print(this->mode);
    // Serial.print(" ");
    // Serial.println(this->modes[this->mode]->Name());
    //disp.print(this->modes[this->mode]->Name() , 1);


}

void Raincouver::Prev() {
    Serial.print("Prev:");
    // I'm too lazy to check how mod works with negative numbers.
    this->mode = (this->mode + (RAINCOUVER_MODES - 1)) % RAINCOUVER_MODES;
    Serial.print(this->mode);
    Serial.print(" ");

    Serial.println(this->modes[this->mode]->Name());
}

void Raincouver::Up() {

    this->modes[this->mode]->Up();

}

void Raincouver::Down() {
    this->modes[this->mode]->Down();
}

void Raincouver::Number(int val) {
    this->modes[this->mode]->Number(val);
}


void drawSky() {
    for (int i = 0; i < 64; i++) {
        leds[address(448+i)] = CRGB(0x101010);
    }
}





void Raincouver::DrawNextFrame(unsigned long frameCount) {
    drawSky();

    for(int i=0; i < this->drops * 1; i++) {
        Point* p1 = new Point();
        // In theory knowing x and y speed we could do a better job of finding rain drops that cross the visual plane
        // But oh well
        p1->x = random(8 + 2* abs(this->xSpeed)) - abs(this->xSpeed);
        p1->y = random(8 + 2* abs(this->ySpeed)) - abs(this->ySpeed);
        p1->z = 6;

        Point* p2 = new Point();
        p2->x = p1->x + this->xSpeed;
        p2->y = p1->y + this->ySpeed;
        p2->z = -1;

        CRGB c = CRGB(random(0x0F) + 0xF0);

        // sprintf(buffer, "Start: (%d,%d,%d) -> End: (%d,%d,%d), Current: (%d)", p1->x, p1->y, p1->z, p2->x, p2->y, p2->z, c);

        // Serial.println(buffer);
        am.AddAnimation(new MovingPoint(this->frames, p1, p2, c, true));
    }

    am.ProcessAnimations();

}
