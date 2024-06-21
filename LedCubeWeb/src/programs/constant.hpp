#ifndef LEDCUBEWEB_CONSTANT_COLOUR_HPP
#define LEDCUBEWEB_CONSTANT_COLOUR_HPP

#include "programs.hpp"



class ConstantColor : public Program {


public:
    ConstantColor() {

        modes[0] = new RemoteControlledInt("red", &red, 'r');
        modes[1] = new RemoteControlledInt("green", &green, 'g');
        modes[2] = new RemoteControlledInt("blue", &blue, 'b');
    }

    void Next() override;
    void Prev() override;
    void Up() override;
    void Down() override;
    void Number(int val) override;

    uint8_t Icon() override {
        return this->modes[mode]->Icon();
    }

protected:
    virtual void DrawNextFrame(unsigned long frameCounter) override;


private:
    int red = 8;
    int green = 8;
    int blue = 8;
    int mode = 0;
    RemoteControlledInt *modes[3];


};


#endif //LEDCUBEWEB_CONSTANT_COLOUR_HPP