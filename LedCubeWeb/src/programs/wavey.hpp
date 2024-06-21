#ifndef LEDCUBEWEB_WAVEY_HPP
#define LEDCUBEWEB_WAVEY_HPP

#include "programs.hpp"


#define WAVEY_MODES 5
class Wavey : public Program {


public:
    Wavey() {

        modes[0] = new RemoteControlledInt("A", &A, 'A');
        modes[1] = new RemoteControlledInt("B", &B, 'B');
        modes[2] = new RemoteControlledInt("C", &C, 'C');
        modes[3] = new RemoteControlledInt("D", &D, 'D');
        modes[4] = new RemoteControlledInt("W", &W, 'W');


        //modes[1] = new RemoteControlledInt("phase", &phase, CRGB(0x001000));
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
    int A = 1;
    int B = 0;
    int C = 1;
    int D = 0;
    int W = 80;
    int frames = 0;
    int mode = 0;
    RemoteControlledInt *modes[WAVEY_MODES];


};


#endif //LEDCUBEWEB_WAVEY_HPP