//
// Created by sjr on 3/31/24.
//

#ifndef LEDCUBEWEB_REMOTE_CONTROLLED_INT_HPP
#define LEDCUBEWEB_REMOTE_CONTROLLED_INT_HPP
#include "Arduino.h"

class RemoteControlledInt {
private:
    char  *name;
    int *val;
    uint8_t icon;
public:
    RemoteControlledInt(char* name, int *val, char icon) : name(name), val(val), icon(icon) {

    }

    void Up() {
        (*val)++;
        Serial.print("Incrementing ");
        Serial.print(name);
        Serial.print(" to: ");
        Serial.println(*val);
    }

    void Down() {
        (*val)--;
        Serial.print("Decrementing ");
        Serial.println(name);
        Serial.print(" to: ");
        Serial.println(*val);
    }

    void Number(int number){
        Serial.print("Setting");
        Serial.print(name);
        Serial.print(" to: ");
        Serial.println(number);
        *val = number;
    }

    char* Name() {
        return name;
    }

    uint8_t Icon() {
        return this->icon;
    }


};
#endif //LEDCUBEWEB_REMOTE_CONTROLLED_INT_HPP
