#ifndef LEDCUBEWEB_HEAVEN_HPP
#define LEDCUBEWEB_HEAVEN_HPP

#include "programs.hpp"



#define HEAVEN_MODES 2

class Heaven : public Program {


public:
    Heaven() {

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
    RemoteControlledInt *modes[HEAVEN_MODES];


};


#endif //LEDCUBEWEB_HEAVEN_HPP