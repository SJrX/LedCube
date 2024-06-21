#include "heaven.hpp"
#include "animations/animations_manager.hpp"


void Heaven::Next() {
    // Serial.print("Next:");
    this->mode = (this->mode + 1) % HEAVEN_MODES;


    // Serial.print(this->mode);
    // Serial.print(" ");
    // Serial.println();
}

void Heaven::Prev() {
    Serial.print("Prev:");
    // I'm too lazy to check how mod works with negative numbers.
    this->mode = (this->mode + (HEAVEN_MODES - 1)) % HEAVEN_MODES;
    Serial.print(this->mode);
    Serial.print(" ");

    Serial.println(this->modes[this->mode]->Name());
}

void Heaven::Up() {

    this->modes[this->mode]->Up();

}

void Heaven::Down() {
    this->modes[this->mode]->Down();
}

void Heaven::Number(int val) {
    this->modes[this->mode]->Number(val);
}



void Heaven::DrawNextFrame(unsigned long frameCount) {



    // The number of drops is a function of how long we draw a drop for.
    // and if we make the speed less it is more likely hit
    if (random(this->speed * 10) < this->drops * 2) {

        Point* p1 = new Point();
        // In theory knowing x and y speed we could do a better job of finding rain drops that cross the visual plane
        // But oh well
        p1->x = random(8);
        p1->y = random(8);
        p1->z = 0;

        Point* p2 = new Point();
        p2->x = p1->x;
        p2->y = p1->y;
        p2->z = 7;

        CRGB c = CRGB(0xaa8800);


        am.AddAnimation(new MovingPoint(this->speed * 10, p1, p2, c, true));

    }

    am.ProcessAnimations();


}