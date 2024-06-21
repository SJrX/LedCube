#ifndef LEDCUBEWEB_SNAKE_HPP
#define LEDCUBEWEB_SNAKE_HPP

#include "programs.hpp"


#define SNAKE_MODES 2
class Snake : public Program {


public:
    Snake() {

        modes[0] = new RemoteControlledInt("drops", &drops, '#');
        modes[1] = new RemoteControlledInt("speed", &speed, 's');

        //modes[3] = new RemoteControlledInt("frames", &frames, CRGB(0xFFFFFF));


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

    int drops = 5;
    int speed = 10;

    int mode = 0;

    RemoteControlledInt *modes[SNAKE_MODES];

};


#endif //LEDCUBEWEB_SNAKE_HPP