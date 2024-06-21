#ifndef LEDCUBEWEB_RGB_HPP
#define LEDCUBEWEB_RGB_HPP

#include "programs.hpp"


#define RGB_MODES 5


class Rgb : public Program {


public:
    Rgb() {

        modes[0] = new RemoteControlledInt("red", &red, 'r');
        modes[1] = new RemoteControlledInt("green", &green, 'g');
        modes[2] = new RemoteControlledInt("blue", &blue, 'b');
        modes[3] = new RemoteControlledInt("delta", &delta, 'd');
        modes[4] = new RemoteControlledInt("frequency", &frequency, 'f');

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
    int red = random(64);
    int green = random(64);
    int blue = random(64);
    int delta = 1;
    int frequency = 40;
    int mode = 0;
    RemoteControlledInt *modes[RGB_MODES];


};


#endif //LEDCUBEWEB_RGB_HPP