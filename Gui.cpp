//
// Created by alber on 29/11/2022.
//

#include "Gui.h"

Gui::Gui() {
    loadTextures();
    std::cout << "i'm GUI constructor" << std::endl;
    healthBar.setTexture(texManager.getTextureRef("healthBar"));

    std::string numberOrTitlesFontFile = "res/fonts/bloody.ttf";
    std::string textFontFile = "res/fonts/fffforwa.ttf";
    try {
        if (!numbersOrTitlesFont.loadFromFile(numberOrTitlesFontFile))
            throw GameException("Error opening numbersOrTitlesFont file", numberOrTitlesFontFile, false);
        if (!textFont.loadFromFile(textFontFile))
            throw GameException("Error opening textFontFile file", textFontFile, false);
    } catch (GameException &e) {}


    pointsIndicator.setFont(textFont);
    pointsIndicator.setCharacterSize(textFontSize);
    pointsIndicator.setFillColor(sf::Color::White);

    roundIndicator.setFont(numbersOrTitlesFont);
    roundIndicator.setCharacterSize(titleFontSize);
    roundIndicator.setFillColor(sf::Color(102, 0, 0));

    this->pointsDisplayed = "0000000000";
    this->roundDisplayed = "1";
}

void Gui::loadTextures() {
    texManager.loadTexture("healthBar", "res/textures/progressbar.png");
}

void Gui::drawGui(sf::RenderWindow &window) {
    //draw HealthBar
    int posXHealth = abs(5 * 32 - window.getSize().x) - 16; //"16" is a distance from window limits
    sf::Vector2f worldPosHealth = window.mapPixelToCoords({posXHealth, 16});
    healthBar.setPosition(worldPosHealth);
    window.draw(healthBar);

    //draw PointsIndicator
    int posXPoints = abs(window.getSize().x / 2 - textFontSize * (totalDigits / 2 - 1));
    sf::Vector2f worldPosPoints = window.mapPixelToCoords({posXPoints, 16}); //"16" is a distance from window limits
    pointsIndicator.setPosition(worldPosPoints);
    pointsIndicator.setString(pointsDisplayed);
    window.draw(pointsIndicator);

    //draw RoundIndicator
    sf::Vector2f worldPosRound = window.mapPixelToCoords({16, 16}); //"16" is a distance from window limits
    roundIndicator.setPosition(worldPosRound);
    roundIndicator.setString(roundDisplayed);
    window.draw(roundIndicator);

}

void Gui::updateHealthBar(int hp) {
    int totalHP = 20; //this is to be equal to mike total HP
    healthBar.setTextureRect({0, 0, (5 * 32 * hp) / totalHP, 32});
}

TextureManager Gui::getTexManager() {
    return texManager;
}

const sf::Sprite &Gui::getHealthBar() const {
    return healthBar;
}

void Gui::updatePoints(unsigned int points) {
    std::string digits = std::to_string(points);
    unsigned int numDigits = digits.size();
    std::string zeros = "0";

    if (numDigits != totalDigits) {
        if (numDigits == totalDigits - 1)
            this->pointsDisplayed = zeros + digits;
        else {
            for (int i = 0; i < totalDigits - numDigits; i++)
                zeros += "0";
            this->pointsDisplayed = zeros + digits;
        }
    } else
        this->pointsDisplayed = digits;
}

const std::string &Gui::getPointsDisplayed() const {
    return pointsDisplayed;
}

void Gui::updateRound(int round) {
    std::string roundString = std::to_string(round);
    this->roundDisplayed = roundString;
}

