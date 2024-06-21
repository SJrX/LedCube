//
// Created by sjr on 4/1/24.
//

#ifndef LEDCUBEWEB_ANIMATIONS_MANAGER_HPP
#define LEDCUBEWEB_ANIMATIONS_MANAGER_HPP

#include "animations.hpp"

#define MAX_ANIMATIONS 250


class AnimationManager {
public:
    AnimationManager() {

    }
    bool AddAnimation(Animation* a);
    void ClearAnimations();
    void ProcessAnimations();
    bool AllAnimationsDone();
private:
    Animation *animations[MAX_ANIMATIONS];
    int animationCount = 0;
};

extern AnimationManager am;

#endif //LEDCUBEWEB_ANIMATIONS_MANAGER_HPP
