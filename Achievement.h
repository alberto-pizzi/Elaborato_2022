//
// Created by alber on 21/01/2023.
//

#ifndef ELABORATO_ACHIEVEMENT_H
#define ELABORATO_ACHIEVEMENT_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include "GameException.h"


class Achievement {
private:

    //sprites
    sf::Sprite boxSprite;
    sf::Sprite trophySprite;
    static float previousBoxPosY;
    bool posAlreadySet = false;
    bool firstTime = true;

    //info
    std::string name;
    std::string description;

    //colors
    const sf::Color tarnishColor = sf::Color(47, 47, 47);
    const sf::Color barColor = sf::Color(99, 151, 208);
    const sf::Color achievedBarColor = sf::Color(8, 69, 126);

    //progress
    unsigned int actualProgress = 0;
    unsigned int targetProgress;

    //progress bar
    sf::RectangleShape progressBar;
    sf::RectangleShape shadowProgressBar;
    const sf::Vector2f borderDistance = {28, 28};
    sf::Font progressTextFont;
    std::string progress;
    sf::Text achievementNameText;
    int barTextFontSize = 20;
    sf::Text progressText;
    bool achieved = false;

public:
    Achievement(const sf::Texture &boxTex, const sf::Texture &trophyTex, const std::string &name,
                const std::string &description,
                unsigned int goal, const sf::Font &font);

    bool isAchieved() const;

    void update(unsigned int value);

    void drawAchievement(sf::RenderWindow &window);

    unsigned int getActualProgress() const;

    const sf::Sprite &getBoxSprite() const;

    const sf::Sprite &getTrophySprite() const;

    const std::string &getProgress() const;

};


#endif //ELABORATO_ACHIEVEMENT_H
