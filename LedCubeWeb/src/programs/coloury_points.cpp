#include "coloury_points.hpp"
#include "../animations/animations_manager.hpp"


void ColouryPoints::Next() {
    // Serial.print("Next:");
    this->mode = (this->mode + 1) % COLOURY_POINTS_MODES;


    // Serial.print(this->mode);
    // Serial.print(" ");
    // Serial.println();
}

void ColouryPoints::Prev() {
    Serial.print("Prev:");
    // I'm too lazy to check how mod works with negative numbers.
    this->mode = (this->mode + (COLOURY_POINTS_MODES - 1)) % COLOURY_POINTS_MODES;
    Serial.print(this->mode);
    Serial.print(" ");

    Serial.println(this->modes[this->mode]->Name());
}

void ColouryPoints::Up() {

    this->modes[this->mode]->Up();

}

void ColouryPoints::Down() {
    this->modes[this->mode]->Down();
}

void ColouryPoints::Number(int val) {
    this->modes[this->mode]->Number(val);
}



void ColouryPoints::DrawNextFrame(unsigned long frameCount) {
    // The number of drops is a function of how long we draw a drop for.
    // and if we make the speed less it is more likely hit
    if (random(this->speed * 10) < this->drops * 2) {

        Point* p1 = new Point();
        // In theory knowing x and y speed we could do a better job of finding rain drops that cross the visual plane
        // But oh well
        p1->x = random(16) - 4;
        p1->y = random(16) - 4;
        p1->z = random(16) - 4;

        Point* p2 = new Point();
        p2->x = random(16) - 4;
        p2->y = random(16) - 4;
        p2->z = random(16) - 4;

        CRGB c = CRGB(random(0xFFFFFF));


        am.AddAnimation(new MovingPoint(this->speed * 25, p1, p2, c, true));
    }
    am.ProcessAnimations();
}
