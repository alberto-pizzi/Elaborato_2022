//
// Created by alber on 23/11/2022.
//

#include "Animation.h"


void Animation::update(float dt) {
    currentFrameTime += dt;
    if (currentFrameTime >= frameTime) {
        currentFrameTime -= frameTime;
        currentFrame++;
        if (currentFrame >= frames.size())
            currentFrame = 0;
    }
}

void Animation::reset() {
    currentFrame = 0;
    currentFrameTime = 0;
}

Animation::Animation(std::vector<sf::IntRect> &frames, float duration)
        : frames(frames), frameTime(duration / static_cast<float>(frames.size())) {
    reset();
}

void Animation::setAnimation(std::vector<sf::IntRect> &frames, float duration, int direction) {
    this->frames = frames;
    this->frameTime = duration / static_cast<float>(frames.size());
    if (oldDirection != direction)
        reset();
    oldDirection = direction;
}

sf::IntRect &Animation::getCurrentRect() const {
    return frames[currentFrame];
}