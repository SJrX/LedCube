
#include <Arduino.h>
#include "Arduino_LED_Matrix.h"
#include <FastLED.h>
#include "WiFiS3.h"
#include "arduino_secrets.h"
#include <main.hpp>
#include "wifi.hpp"
#include "leds.hpp"
#include "drawing.hpp"
#include "characters.h"
#include "programs/programs.hpp"
#include "ir.hpp"

#include "programs/program_manager.hpp"
#include "matrix_manager.hpp"

ArduinoLEDMatrix matrix;

int led = LED_BUILTIN;




void setup() {
    Serial.begin(115200);
    Serial.println("*** Reboot ***"); // initialize serial communication
    pinMode(led, OUTPUT);  // set the LED pin mode
    randomSeed(analogRead(0));

    matrix.begin();
    initWifi();

    rm.init();
    initLeds();
    mm.init();
    Serial.println("Done Setup");

}

int offset = 0;

int counter = 0;

unsigned long StartTime = 0;


#define FRAMES_PER_SECOND 40

uint8_t lastMode = 0;

const long neededTime = 1000 / FRAMES_PER_SECOND;

void loop() {

    //Serial.println("Loop");
    // put your main code here, to run repeatedly:
    // Turn the LED on, then pause
    unsigned long loopStart = micros();

    if (!rm.ProcessIRAndCheckIfShouldContinue()) {
        return;
    }


    if (rm.IsPaused()) {
        delay(neededTime);
        return;
    }

    Program *p = pm.CurrentProgram();

   mm.SetIcon(p->Icon());



    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }

//    FastLED.show();

    p->NextFrame();


    FastLED.show();

    long duration = (micros() - loopStart) / 1000;


    long delayTime = max(0, neededTime - duration);

//
//     Serial.print("Effective FPS:");
//     if (delayTime > 0) {
//       Serial.println(FRAMES_PER_SECOND);
//     } else {
//       Serial.println(1000.0 / duration);
//     }



//    delay(100);
    delay(delayTime);
}