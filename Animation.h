//
// Created by alber on 23/11/2022.
//

#ifndef ELABORATO_ANIMATION_H
#define ELABORATO_ANIMATION_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

static int oldDirection = 5; //casual number (not 0 <= number < 4)

class Animation {
public:
    Animation(std::vector<sf::IntRect> &frames, float duration);

    void setMovementAnimation(std::vector<sf::IntRect> &frames, float duration, int direction);

    void setNotCyclicalAnimation(std::vector<sf::IntRect> &frames, float duration);

    void reset();

    void update(float dt);

    void updateNotCyclicalAnimation(float dt, bool &end, bool &isAnimationActive);

    sf::IntRect &getCurrentRect() const;

    std::vector<sf::IntRect> &frames;
    std::vector<sf::IntRect> &idleFrames;
private:

    float frameTime;
    int currentFrame;
    float currentFrameTime;
};

#endif //ELABORATO_ANIMATION_H
