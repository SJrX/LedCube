//
// Created by sjr on 4/1/24.
//

#ifndef LEDCUBEWEB_IR_HPP
#define LEDCUBEWEB_IR_HPP
#include "matrix_manager.hpp"
#define IR_PIN 6


class RemoteManager {
public:
    RemoteManager() = default;
    void init();

    bool ProcessIRAndCheckIfShouldContinue();

    bool IsPaused();
private:
    bool paused = false;
    void TranslateIR(uint32_t code);
};

extern RemoteManager rm;

#endif //LEDCUBEWEB_IR_HPP
