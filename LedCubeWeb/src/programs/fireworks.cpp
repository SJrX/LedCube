#include "fireworks.hpp"
#include "animations/animations_manager.hpp"


void Fireworks::Next() {
    // Serial.print("Next:");
    this->mode = (this->mode + 1) % FIREWORKS_MODES;


    // Serial.print(this->mode);
    // Serial.print(" ");
    // Serial.println();
}

void Fireworks::Prev() {
    Serial.print("Prev:");
    // I'm too lazy to check how mod works with negative numbers.
    this->mode = (this->mode + (FIREWORKS_MODES - 1)) % FIREWORKS_MODES;
    Serial.print(this->mode);
    Serial.print(" ");

    Serial.println(this->modes[this->mode]->Name());
}

void Fireworks::Up() {

    this->modes[this->mode]->Up();

}

void Fireworks::Down() {
    this->modes[this->mode]->Down();
}

void Fireworks::Number(int val) {
    this->modes[this->mode]->Number(val);
}


int drops = 0;
boolean fired = false;
int lastX = 0;
int lastY = 0;
int lastZ = 0;
CRGB lastColor;

void Fireworks::DrawNextFrame(unsigned long frameCount) {



    // The number of drops is a function of how long we draw a drop for.
    // and if we make the speed less it is more likely hit
    if (drops-- < 0) {

        if (fired) {
            Serial.println("Explosion");

            fired = false;
            drops=this->speed * 10;

            for(int i=0; i < 150; i++) {
                Point* p1 = new Point();
                // In theory knowing x and y speed we could do a better job of finding rain drops that cross the visual plane
                // But oh well
                p1->x = lastX;
                p1->y = lastY;
                p1->z = lastZ;

                Point* p2 = new Point();
                p2->x = random(72)-32;
                p2->y = random(72)-32;
                p2->z = random(72)-32;


                CRGB c = CRGB(lastColor.red + random(0x20), lastColor.green + random(0x20), lastColor.blue + random(0x20));


                am.AddAnimation(new ParabolicTrajectory(this->speed * 10, p1, p2, c, true, 0));
            }
        } else {
            Serial.println("Starting frame");

            fired = true;

            drops+=this->speed * 10;
            Point* p1 = new Point();
            // In theory knowing x and y speed we could do a better job of finding rain drops that cross the visual plane
            // But oh well
            p1->x = random(8);
            p1->y = random(8);
            p1->z = 0;

            Point* p2 = new Point();
            p2->x = random(8);
            p2->y = random(8);
            p2->z = random(5)+3;

            lastX = p2->x;
            lastY = p2->y;
            lastZ = p2->z;

            CRGB c = CRGB(random(0xFFFFFF));

            lastColor = c;

            am.AddAnimation(new ParabolicTrajectory(this->speed * 10, p1, p2, c, true, 0));

        }
    }

    am.ProcessAnimations();

}