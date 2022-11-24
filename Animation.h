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

static int oldDirection = 5;

class Animation {
public:
    Animation(std::vector<sf::IntRect> &frames, float duration);

    void setAnimation(std::vector<sf::IntRect> &frames, float duration, int direction);

    void reset();

    void update(float dt);

    sf::IntRect &getCurrentRect() const;

    std::vector<sf::IntRect> &frames;
private:

    float frameTime;
    int currentFrame;
    float currentFrameTime;
};

#endif //ELABORATO_ANIMATION_H
