//
// Created by alber on 21/01/2023.
//

#include "Achievement.h"

Achievement::Achievement(const sf::Texture &boxTex, const sf::Texture &trophyTex, std::string name,
                         std::string description,
                         unsigned int goal)
        : boxTexture(boxTex), trophyTexture(trophyTex), name(std::move(name)), description(std::move(description)),
          targetProgress(goal) {

    //FIXME

    std::string actualProgressString = std::to_string(actualProgress);
    std::string goalProgressString = std::to_string(goal);

    progress = actualProgressString + " / " + goalProgressString;

    boxSprite.setTexture(boxTex);
    trophySprite.setTexture(trophyTex);

    if (isAchieved())
        achieved = true;

}

void Achievement::drawAchievement(sf::RenderWindow &window) {
    if (achieved)
        trophySprite.setColor(sf::Color::White);
    else
        trophySprite.setColor(tarnishColor);
    window.draw(boxSprite);
    window.draw(trophySprite);
}

bool Achievement::isAchieved() const {
    if (actualProgress >= targetProgress)
        return true;
    else
        return false;
}

void Achievement::update(unsigned int value) {
    actualProgress += value;

    std::string actualProgressString = std::to_string(actualProgress);
    std::string goalProgressString = std::to_string(targetProgress);
    progress = actualProgressString + " / " + goalProgressString;

    if (isAchieved())
        achieved = true;
}

unsigned int Achievement::getActualProgress() const {
    return actualProgress;
}
