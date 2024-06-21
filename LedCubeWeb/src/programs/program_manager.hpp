//
// Created by sjr on 4/1/24.
//

#ifndef LEDCUBEWEB_PROGRAM_MANAGER_HPP
#define LEDCUBEWEB_PROGRAM_MANAGER_HPP
#include "programs.hpp"

#include "coloury_points.hpp"
#include "constant.hpp"
#include "fireworks.hpp"
#include "heaven.hpp"

#include "raincouver.hpp"
#include "snake.hpp"
#include "wavey.hpp"
#include "rgb.hpp"

#include "animations/animations_manager.hpp"

#define PROGRAMS 8
class ProgramManager {
public:
    ProgramManager() {
        programs[0] = new ColouryPoints();
        programs[1] = new ConstantColor();
        programs[2] = new Fireworks();
        programs[3] = new Heaven();
        programs[4] = new Raincouver();
        programs[5] = new Snake();
        programs[6] = new Wavey();
        programs[7] = new Rgb();

    }

    void NextProgram() {
        this->currentProgram = (this->currentProgram + 1) % PROGRAMS;
        am.ClearAnimations();
    }

    Program* CurrentProgram() {
        return this->programs[this->currentProgram];
    }

private:
    Program* programs[PROGRAMS];

    int currentProgram = 5;
};

extern ProgramManager pm;
#endif //LEDCUBEWEB_PROGRAM_MANAGER_HPP
