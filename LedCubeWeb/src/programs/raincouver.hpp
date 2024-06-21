#ifndef LEDCUBEWEB_RAINCOUVER_HPP
#define LEDCUBEWEB_RAINCOUVER_HPP

#include "programs.hpp"


#define RAINCOUVER_MODES 4

class Raincouver : public Program {


public:
    Raincouver() {

        modes[0] = new RemoteControlledInt("Drops", &drops,  '#');
        modes[1] = new RemoteControlledInt("X-Speed", &xSpeed, 'X');
        modes[2] = new RemoteControlledInt("Y-Speed", &ySpeed, 'Y');
        modes[3] = new RemoteControlledInt("Frames", &frames, 'F');
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
    int xSpeed = 0;
    int ySpeed = 0;
    int drops = 1;
    int frames = 12;
    int mode = 0;

    RemoteControlledInt *modes[RAINCOUVER_MODES];

};



#endif //LEDCUBEWEB_RAINCOUVER_HPP