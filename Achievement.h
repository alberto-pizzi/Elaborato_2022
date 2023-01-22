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


class Achievement {
private:

    sf::Sprite boxSprite;
    sf::Sprite trophySprite;

    //info
    std::string name;
    std::string description;

    //colors
    const sf::Color tarnishColor = sf::Color(47, 47, 47);

    //progress
    unsigned int actualProgress = 0;
    unsigned int targetProgress;

    //progress bar
    sf::RectangleShape progressBar;
    std::string progress;
    sf::Text achievementNameText;
    sf::Text progressText;
    bool achieved = false;

public:
    Achievement(const sf::Texture &boxTex, const sf::Texture &trophyTex, std::string name, std::string description,
                unsigned int goal);

    bool isAchieved() const;

    void update(unsigned int value);

    void drawAchievement(sf::RenderWindow &window);

    unsigned int getActualProgress() const;

};


#endif //ELABORATO_ACHIEVEMENT_H
