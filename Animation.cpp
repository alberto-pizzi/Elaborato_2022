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
        : frames(frames), idleFrames(frames), frameTime(duration / static_cast<float>(frames.size())) {
    reset();
}

void Animation::setMovementAnimation(std::vector<sf::IntRect> &frames, float duration, int direction) {
    this->frames = frames;
    this->frameTime = duration / static_cast<float>(frames.size());
    if (oldDirection != direction)
        reset();
    oldDirection = direction;
}

sf::IntRect &Animation::getCurrentRect() const {
    return frames[currentFrame];
}

void Animation::setNotCyclicalAnimation(std::vector<sf::IntRect> &frames, float duration) {
    this->frames = frames;
    this->frameTime = duration / static_cast<float>(frames.size());
    reset();
    this->originalAnimationSizeX = frames[0].width;
}

void Animation::updateNotCyclicalAnimation(float dt, bool &end, bool &isActiveAnimation) {
    if (isActiveAnimation && (!end)) {
        currentFrameTime += dt;
        if (currentFrameTime >= frameTime) {
            currentFrameTime -= frameTime;
            currentFrame++;
            if (currentFrame >= frames.size()) {
                end = true;
                currentFrame = 0;
            }
        }
    } else {
        end = false;
        isActiveAnimation = false;
        currentFrame = 0;
        setNotCyclicalAnimation(idleFrames, 10.f);
    }
}

int Animation::getOriginalAnimationSizeX() const {
    return originalAnimationSizeX;
}
