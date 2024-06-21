//
// Created by sjr on 4/1/24.
//

#include "animations_manager.hpp"

AnimationManager am = AnimationManager();

bool AnimationManager::AllAnimationsDone() {
    return this->animations[0] == 0;
}

void AnimationManager::ProcessAnimations() {

    for (int i = 0; i < animationCount; ) { // Remove increment from here
        if (animations[i]->done()) {

            delete animations[i];

            animationCount--;
            animations[i] = animations[animationCount]; // Move the last animation to this spot
            animations[animationCount] = 0; // Nullify the last spot

            // Don't increment i, so we check the newly swapped animation next
        } else {
            animations[i]->draw();
            i++; // Only increment if we don't remove the animation
        }
    }

    return;
}

boolean AnimationManager::AddAnimation(Animation* a) {
    if (animationCount < MAX_ANIMATIONS) {
        animations[animationCount++] = a;
    } else {
        delete a;
        return false;
        Serial.println(F("WARN: Max animations reached"));
        //memDump();
    }

    return true;
}

void AnimationManager::ClearAnimations() {
    for (int i = 0; i < animationCount; i++) { // Remove increment from here
        delete animations[i];
        animations[i] = 0;
    }
    animationCount = 0;
}
