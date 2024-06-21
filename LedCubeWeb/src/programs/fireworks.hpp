#ifndef LEDCUBEWEB_FIREWORKS_HPP
#define LEDCUBEWEB_FIREWORKS_HPP

#include "programs.hpp"


#define FIREWORKS_MODES 2

class Fireworks : public Program {


public:
    Fireworks() {

        modes[0] = new RemoteControlledInt("drops", &drops, '#');
        modes[1] = new RemoteControlledInt("speed", &speed, 's');
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
    int drops = 1;
    int speed = 20;
    int mode = 0;
    RemoteControlledInt *modes[FIREWORKS_MODES];


};



#endif //LEDCUBEWEB_FIREWORKS_HPP