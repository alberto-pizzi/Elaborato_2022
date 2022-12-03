//
// Created by alber on 29/11/2022.
//

#ifndef ELABORATO_GUI_H
#define ELABORATO_GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "TextureManager.h"
#include "GameException.h"

class Gui {
private:
    void loadTextures();

    TextureManager texManager;
    sf::Sprite healthBar;
    sf::Font numbersOrTitlesFont;
    sf::Font textFont;
    sf::Text pointsIndicator;
    int textFontSize = 24;
    std::string pointsDisplayed = "0000000000";
    const int totalDigits = 10;
public:
    Gui();

    const std::string &getPointsDisplayed() const;

    const sf::Sprite &getHealthBar() const;

    void message(std::string message);

    void updateHealthBar(int hp);

    void updateArmor(int armor);

    void updatePoints(unsigned int points);

    void drawGui(sf::RenderWindow &window);

    TextureManager getTexManager();

};


#endif //ELABORATO_GUI_H
