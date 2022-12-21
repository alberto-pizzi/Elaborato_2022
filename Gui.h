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
#include "GameCharacter.h"

class Gui {
private:
    void loadTextures();

    sf::Texture weaponTexture;
    sf::Sprite weaponSpriteIndicator;
    sf::Vector2f hitBoxWeaponSize;

    TextureManager texManager;

    sf::Sprite healthBar;
    sf::Font numbersOrTitlesFont;
    sf::Font textFont;
    sf::Text pointsIndicator;
    sf::Text roundIndicator;
    int textFontSize = 24;
    int titleFontSize = 24;

    //colors
    const sf::Color semiTransparentGreyGuiColor = sf::Color(239, 239, 239, 150);
    const sf::Color redGuiColor = sf::Color(102, 0, 0, 200);
    const sf::Color yellowGuiColor = sf::Color(255, 216, 0, 200);

    //magazine indicator
    sf::Text remainingBulletsIndicator;
    sf::Text totalBulletsIndicator;
    int remainingBulletsTextSize = 20;
    int totalBulletsTextSize = 10;
    std::string remainingBulletsDisplayed;
    std::string totalBulletsDisplayed;
    sf::RectangleShape designSeparator;

    std::string pointsDisplayed;
    std::string roundDisplayed;
    const int totalDigits = 10;
    sf::Vector2i distanceFromWindowLimits = {16, 16};
public:
    Gui(unsigned int points, int round, int remainingBullets, int totalBullets, bool infiniteBullets,
        const sf::Texture &weaponTexture, const TextureManager &guiTexManager);

    const std::string &getPointsDisplayed() const;

    const sf::Sprite &getHealthBar() const;

    void message(std::string message);

    void updateHealthBar(int hp);

    void
    updateWeaponType(const sf::Texture &newWeaponTexture, const sf::IntRect &idleFrame, const sf::Vector2f &hitboxSize);

    void updateArmor(int armor);

    void updateRound(int round);

    void updatePoints(unsigned int points);

    void updateMagazines(int remaining, int total, bool isInfinite);

    void drawGui(sf::RenderWindow &window);

    TextureManager getTexManager();

};


#endif //ELABORATO_GUI_H
