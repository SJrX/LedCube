#include "snake.hpp"
#include "animations/animations_manager.hpp"


void Snake::Next() {
    // Serial.print("Next:");
    this->mode = (this->mode + 1) % SNAKE_MODES;


    // Serial.print(this->mode);
    // Serial.print(" ");
    // Serial.println();
}

void Snake::Prev() {
    Serial.print("Prev:");
    // I'm too lazy to check how mod works with negative numbers.
    this->mode = (this->mode + (SNAKE_MODES - 1)) % SNAKE_MODES;
    Serial.print(this->mode);
    Serial.print(" ");

    Serial.println(this->modes[this->mode]->Name());
}

void Snake::Up() {

    this->modes[this->mode]->Up();

}

void Snake::Down() {
    this->modes[this->mode]->Down();
}

void Snake::Number(int val) {
    this->modes[this->mode]->Number(val);
}

#define DIRECTION_UP 0
#define DIRECTION_NORTH 1
#define DIRECTION_EAST 2
#define DIRECTION_SOUTH 3
#define DIRECTION_WEST 4
#define DIRECTION_DOWN 5

int* allowedTurns(int direction) {
    switch(direction) {
        case DIRECTION_UP:
        case DIRECTION_DOWN:
            static int arr[] = { DIRECTION_NORTH, DIRECTION_EAST, DIRECTION_SOUTH, DIRECTION_WEST };
            return arr;
        case DIRECTION_EAST:
        case DIRECTION_WEST:
            static int arr1[] = { DIRECTION_NORTH, DIRECTION_UP, DIRECTION_SOUTH, DIRECTION_DOWN };
            return arr1;
        default:
            static int arr2[] = { DIRECTION_EAST, DIRECTION_UP, DIRECTION_WEST, DIRECTION_DOWN };
            return arr2;
    }
}

int snakeLength = 1;
#define MAX_SNAKE_LENGTH 512
Point* snakePoints[MAX_SNAKE_LENGTH];
//int snakeHead = 0;

Point* snakePos;

Point* applePos;

int snakeDirection = -1;

int frameUpdates = 10;

int gridSize = 8;


CRGB snakeColor = CRGB::LawnGreen;

boolean snakeDead = false;
void Snake::DrawNextFrame(unsigned long frameCount) {






    //update logic


    bool frameUpdate = false;


    if (frameUpdates < 0) {
        int framesLeft = abs(frameUpdates);

        int anim_time = 10;
        int anim_scale = 10;

        if ((framesLeft / anim_time) % 2 == 0) {
            snakeColor = CRGB(0x60 + (framesLeft % anim_time)*anim_scale);
        } else {
            snakeColor = CRGB(0x60 + anim_scale*anim_time - (framesLeft % anim_time)*anim_scale);
        }

//        if (((framesLeft / 5) % 32) == 0) {
//            snakeColor = CRGB(0x60);
//        } else {
//            snakeColor = CRGB(0x80);
//        }
    } else {
        snakeColor = CRGB::LawnGreen;
    }


    if ((frameUpdates++ % 3) == 1) {

        if (snakePos == 0) {

            snakeLength = 1;


            snakePos = new Point(random(gridSize-2)+1, random(gridSize-2)+1, random(gridSize-2)+1);

            snakeDirection = DIRECTION_NORTH;
            applePos = new Point(random(gridSize), random(gridSize), random(gridSize));

            snakePoints[0] = snakePos;
            snakeColor = CRGB::LawnGreen;
            snakeDead = false;
        }



        frameUpdate = true;

        //int lastPointIndex = (snakeHead + (snakeLength-1)) % snakeLength;


        // int x = snakePoints[snakeHead]->x;
        // int y = snakePoints[snakeHead]->y;
        // int z = snakePoints[snakeHead]->z;



        for(int i = snakeLength-1; i > 0; i--) {
            snakePoints[i]->x = snakePoints[i-1]->x;
            snakePoints[i]->y = snakePoints[i-1]->y;
            snakePoints[i]->z = snakePoints[i-1]->z;
        }


        Point *head = snakePoints[0];


        int8_t goalX = 4;
        int8_t goalY = 4;
        int8_t goalZ = 4;
        if (applePos != 0) {

            goalX = applePos->x;
            goalY = applePos->y;
            goalZ = applePos->z;

        }

        int scores[6];

        scores[DIRECTION_UP] = abs(head->x-goalX) + abs(head->y - goalY)  + abs(head->z + 1 - goalZ);
        scores[DIRECTION_DOWN] = abs(head->x-goalX) + abs(head->y - goalY)  + abs(head->z - 1 - goalZ);

        scores[DIRECTION_NORTH] = abs(head->x-goalX) + abs(head->y + 1 - goalY)  + abs(head->z - goalZ);
        scores[DIRECTION_SOUTH] = abs(head->x-goalX) + abs(head->y - 1 - goalY)  + abs(head->z- goalZ);

        scores[DIRECTION_EAST] = abs(head->x + 1 - goalX) + abs(head->y - goalY)  + abs(head->z - goalZ);
        scores[DIRECTION_WEST] = abs(head->x - 1 - goalX) + abs(head->y - goalY)  + abs(head->z- goalZ);

        switch(snakeDirection) {
            case DIRECTION_UP:
                scores[DIRECTION_DOWN] = 110;
                break;
            case DIRECTION_DOWN:
                scores[DIRECTION_UP] = 110;
                break;
            case DIRECTION_NORTH:
                scores[DIRECTION_SOUTH] = 110;
                break;
            case DIRECTION_SOUTH:
                scores[DIRECTION_NORTH] = 110;
                break;
            case DIRECTION_EAST:
                scores[DIRECTION_WEST] = 110;
                break;
            case DIRECTION_WEST:
                scores[DIRECTION_EAST] = 110;
                break;
        }

        for (int i=0; i < 6; i++) {
            Point *p = 0;
            switch(i) {
                case DIRECTION_UP:
                    p = new Point(head->x, head->y, head->z+1);
                    break;
                case DIRECTION_DOWN:
                    p = new Point(head->x, head->y, head->z-1);
                    break;
                case DIRECTION_NORTH:
                    p = new Point(head->x, head->y+1, head->z);
                    break;
                case DIRECTION_SOUTH:
                    p = new Point(head->x, head->y-1, head->z);
                    break;
                case DIRECTION_EAST:
                    p = new Point(head->x+1, head->y, head->z);
                    break;
                case DIRECTION_WEST:
                    p = new Point(head->x-1, head->y, head->z);
                    break;
            }


            for (int j = 0; j < snakeLength; j++) {
                Point *snakeSegment = snakePoints[j];

                if ((snakeSegment->x == p->x) && (snakeSegment->y == p->y) && (snakeSegment->z == p->z)) {
                    // Conflict
                    scores[i] = max(scores[i], 100);
                }
            }

            if (p->IsOutOfBounds()) {
                scores[i] = max(100, scores[i]);
            }

            delete p;
        }


        int minDirectionScore = 100;
        int minIndex = 0;
        int offset = random(6);
        Serial.print("(");
        Serial.print(head->x);
        Serial.print(",");
        Serial.print(head->y);
        Serial.print(",");
        Serial.print(head->z);
        Serial.print(")");

        switch(snakeDirection) {
            case DIRECTION_UP:
                Serial.print(":UP => ");
                break;
            case DIRECTION_DOWN:
                Serial.print(":DOWN => ");
                break;
            case DIRECTION_WEST:
                Serial.print(":WEST => ");
                break;
            case DIRECTION_EAST:
                Serial.print(":EAST => ");
                break;
            case DIRECTION_SOUTH:
                Serial.print(":SOUTH => ");
                break;
            case DIRECTION_NORTH:
                Serial.print(":NORTH => ");
                break;
        }


        for (int i = 0; i < 6; i++) {
            int index = (i+offset) % 6;

            if (scores[index] < minDirectionScore) {
                minIndex = index;
                minDirectionScore = scores[index];
            }

            switch(index) {
                case DIRECTION_UP:
                    Serial.print("UP:");
                    break;
                case DIRECTION_DOWN:
                    Serial.print("DOWN:");
                    break;
                case DIRECTION_WEST:
                    Serial.print("WEST:");
                    break;
                case DIRECTION_EAST:
                    Serial.print("EAST:");
                    break;
                case DIRECTION_SOUTH:
                    Serial.print("SOUTH:");
                    break;
                case DIRECTION_NORTH:
                    Serial.print("NORTH:");
                    break;
            }

            Serial.print(scores[index]);
            Serial.print(",");
        }

        snakeDirection = minIndex;
        Serial.print("  ==> ");




        switch(snakeDirection) {
            case DIRECTION_UP:
                Serial.print("UP");
                head->z = (head->z + 1);
                break;
            case DIRECTION_DOWN:
                Serial.print("DOWN");
                head->z = (head->z - 1);
                break;
            case DIRECTION_NORTH:
                Serial.print("NORTH");
                head->y = (head->y + 1);
                break;
            case DIRECTION_SOUTH:
                Serial.print("SOUTH");
                head->y = (head->y  - 1);
                break;
            case DIRECTION_EAST:
                Serial.print("EAST");
                head->x = (head->x + 1);
                break;
            case DIRECTION_WEST:
                Serial.print("WEST");
                head->x = (head->x -1);
                break;
        }

        Serial.println();

        // Check snake death from collision with self.

        // If the snake collided with itself it is dead.
        for (int j = 2; j < snakeLength; j++) {
            Point *snakeSegment = snakePoints[j];

            if ((head->x == snakeSegment->x) && (head->y == snakeSegment->y) && (head->z == snakeSegment->z)) {
                snakeDead = true;

                Serial.print("[DEATH]: Snake collided with self at position: ");
                Serial.println(j);

            }
        }

        if (head->x < 0) {
            snakeDead = true;
            Serial.println("[DEATH]: Snake went too far west");
        }

        if(head->x >= gridSize) {
            snakeDead = true;
            Serial.println("[DEATH]: Snake went too far east");
        }

        if (head->y < 0) {
            Serial.println("[DEATH]: Snake went too far south");
            snakeDead = true;
        }

        if(head->y >= gridSize) {
            Serial.println("[DEATH]: Snake went too far north");
            snakeDead = true;
        }


        if (head->z < 0) {
            Serial.println("[DEATH]: Snake went too low");
            snakeDead = true;
        }

        if(head->z >= gridSize) {
            Serial.println("[DEATH]: Snake went too high");
            snakeDead = true;
        }


        if (snakeDead) {
            frameUpdates = -100;

            for (int j = 0; j < snakeLength; j++) {
                Point *snakeSegment = snakePoints[j];

                Point* p1 = new Point();
                // In theory knowing x and y speed we could do a better job of finding rain drops that cross the visual plane
                // But oh well
                p1->x = snakeSegment->x;
                p1->y = snakeSegment->y;
                p1->z = snakeSegment->z;

                Point* p2 = new Point();
                p2->x = snakeSegment->x;
                p2->y = snakeSegment->y;
                p2->z = -1;

                CRGB c = CRGB(0xFF0000);

                am.AddAnimation(new MovingPoint(25, p1, p2, c, true));
                delete snakePoints[j];
                snakePoints[j] = 0;
            }
            snakeLength = 0;

            if (applePos != 0) {
                delete applePos;
                applePos = 0;
            }

            snakePos = 0;



        }






        if (applePos == 0) {


            applePos = new Point(random(gridSize), random(gridSize), random(gridSize));

            for (int j = 0; j < snakeLength; j++) {
                Point *snakeSegment = snakePoints[j];

                if ((applePos->x == snakeSegment->x) && (applePos->y == snakeSegment->y) && (applePos->z == snakeSegment->z)) {
                    delete applePos;
                    applePos = 0;
                    break;
                }
            }


            snakeColor = CRGB::LawnGreen;
        } else if ((head->x == applePos->x) && (head->y == applePos->y) && (head->z == applePos->z)) {




            frameUpdates = -50;
            delete applePos;
            applePos = 0;


            if (snakeLength < MAX_SNAKE_LENGTH) {
                Point *orig = new Point(snakePoints[snakeLength-1]->x ,snakePoints[snakeLength-1]->y, snakePoints[snakeLength-1]->z);

                snakePoints[snakeLength] = orig;
                snakeLength++;
            }

            Serial.print("[APPLE]: New Snake Length:");
            Serial.println(snakeLength);
        }



    }
    // render

    if (!snakeDead) {

        Point *head = snakePoints[0];




        if (applePos != 0) {
            drawPoint(applePos->x, applePos->y, applePos->z, CRGB::DarkRed);
        }

        //
        drawPoint(head->x, head->y, head->z, snakeColor);



        uint8_t blue = snakeColor.blue;
        uint8_t green = snakeColor.green;

        float fraction = 1.0;
        for(int i = 0; i < snakeLength; i++) {
            Point* p = snakePoints[i];



            drawPoint(p->x, p->y, p->z, CRGB(0, fraction*green, fraction*blue));



            fraction = fraction * 0.95;
        }
    }


    am.ProcessAnimations();

}
