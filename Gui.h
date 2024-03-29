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
    sf::Texture weaponTexture;
    sf::Sprite weaponSpriteIndicator;
    sf::Vector2f hitBoxWeaponSize;

    TextureManager guiTextures;

    sf::Sprite healthBar;
    sf::Sprite shadowHealthBar;
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
    const sf::Color darkGreyColor = sf::Color(47, 47, 47, 255);

    //magazine indicator
    sf::Text remainingBulletsIndicator;
    sf::Text totalBulletsIndicator;
    int remainingBulletsTextSize = 20;
    int totalBulletsTextSize = 10;
    std::string remainingBulletsDisplayed;
    std::string totalBulletsDisplayed;
    sf::RectangleShape designSeparator;

    //countdown indicator
    sf::Text roundCountdownIndicator;
    std::string roundCountdownDisplayed;
    float startNumber;
    bool countdownVisible = true;

    std::string pointsDisplayed;
    std::string roundDisplayed;
    const int totalDigits = 10;
    sf::Vector2i distanceFromWindowLimits = {16, 16};

    //game over
    bool gameOver = false;
    sf::Text gameOverText;
    int gameOverTextSize = 50;

public:
    Gui(unsigned int points, int round, int remainingBullets, int totalBullets, bool infiniteBullets,
        float startRoundCountdownSecond, const sf::Texture &weaponTexture, const TextureManager &guiTexManager);

    const std::string &getPointsDisplayed() const;

    const sf::Sprite &getHealthBar() const;

    void updateHealthBar(float HP, float maxHP);

    void
    updateWeaponType(const sf::Texture &newWeaponTexture, const sf::IntRect &idleFrame, const sf::Vector2f &hitboxSize);

    void updateRound(unsigned int round);

    void updatePoints(unsigned int points);

    void updateMagazines(int remaining, int total, bool isInfinite);

    void updateCountdown(float second, bool start);

    void drawGui(sf::RenderWindow &window);

    TextureManager getTexManager();

    bool isCountdownVisible() const;

    void setCountdownVisible(bool countdownVisible);

    void updateGameOver(bool gameOver);
};


#endif //ELABORATO_GUI_H
