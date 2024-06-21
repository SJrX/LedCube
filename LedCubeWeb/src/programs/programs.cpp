//
// Created by sjr on 4/1/24.
//
#include "programs.hpp"

int Program::NextFrame() {
    this->DrawNextFrame(this->frameCounter++);
}