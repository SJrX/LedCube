//
// Created by sjr on 4/1/24.
//

#ifndef LEDCUBEWEB_MATRIX_MANAGER_HPP
#define LEDCUBEWEB_MATRIX_MANAGER_HPP
#include "simple_matrix.h"

class MatrixManager {
public:
    void init();
    void SetIcon(uint8_t icon);
private:
    simpleMatrix *disp;
    unsigned long lastDisplayTime = 0;
    uint8_t lastIcon = 0;

};

extern MatrixManager mm;

#endif //LEDCUBEWEB_MATRIX_MANAGER_HPP
