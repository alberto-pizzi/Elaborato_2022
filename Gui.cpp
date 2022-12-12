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
    } catch (GameException &e) {
        exit(1); //close all
    }

    //set points indicator
    pointsIndicator.setFont(textFont);
    pointsIndicator.setCharacterSize(textFontSize);
    pointsIndicator.setFillColor(sf::Color::White);
    this->pointsDisplayed = "0000000000";

    //set round indicator
    roundIndicator.setFont(numbersOrTitlesFont);
    roundIndicator.setCharacterSize(titleFontSize);
    roundIndicator.setFillColor(sf::Color(102, 0, 0));
    this->roundDisplayed = "1";

    //set bullets indicator
    remainingBulletsIndicator.setFont(textFont);
    remainingBulletsIndicator.setCharacterSize(remainingBulletsTextSize);
    remainingBulletsIndicator.setFillColor(sf::Color(239, 239, 239, 150));
    this->remainingBulletsDisplayed = "12 "; //this number must be equal to Mike's STARTING bullets

    totalBulletsIndicator.setFont(textFont);
    totalBulletsIndicator.setCharacterSize(totalBulletsTextSize);
    totalBulletsIndicator.setFillColor(sf::Color(239, 239, 239, 150));
    this->totalBulletsDisplayed = "inf";

    designSeparator.setSize(sf::Vector2f(3, 60));
    designSeparator.setFillColor(sf::Color(239, 239, 239, 150));


}

void Gui::loadTextures() {
    texManager.loadTexture("healthBar", "res/textures/progressbar.png");
}

void Gui::drawGui(sf::RenderWindow &window) {
    //draw HealthBar
    int posXHealth =
            abs(texManager.getTextureRef("healthBar").getSize().x - window.getSize().x) - distanceFromWindowLimits.x;
    sf::Vector2f worldPosHealth = window.mapPixelToCoords({posXHealth, distanceFromWindowLimits.y});
    healthBar.setPosition(worldPosHealth);
    window.draw(healthBar);

    //draw PointsIndicator
    int posXPoints = abs(window.getSize().x / 2 - textFontSize * (totalDigits / 2 - 1));
    sf::Vector2f worldPosPoints = window.mapPixelToCoords({posXPoints, distanceFromWindowLimits.y});
    pointsIndicator.setPosition(worldPosPoints);
    pointsIndicator.setString(pointsDisplayed);
    window.draw(pointsIndicator);

    //draw RoundIndicator
    sf::Vector2f worldPosRound = window.mapPixelToCoords(distanceFromWindowLimits);
    roundIndicator.setPosition(worldPosRound);
    roundIndicator.setString(roundDisplayed);
    window.draw(roundIndicator);

    //draw design separator
    sf::Vector2i posDesignSeparator = {distanceFromWindowLimits.x,
                                       static_cast<int>(window.getSize().y - distanceFromWindowLimits.y -
                                                        designSeparator.getSize().y)};
    sf::Vector2f worldPosSeparator = window.mapPixelToCoords(posDesignSeparator);
    designSeparator.setPosition(worldPosSeparator);
    window.draw(designSeparator);

    //draw bullets indicator
    sf::Vector2i posRemainingBullets = {
            static_cast<int>( designSeparator.getGlobalBounds().width) + distanceFromWindowLimits.x * 2 - 6,
            posDesignSeparator.y + 4};
    sf::Vector2f worldPosRemainingBullets = window.mapPixelToCoords(posRemainingBullets);
    remainingBulletsIndicator.setPosition(worldPosRemainingBullets);
    remainingBulletsIndicator.setString(remainingBulletsDisplayed);

    sf::Vector2i posTotalBullets = {posRemainingBullets.x,
                                    posDesignSeparator.y + static_cast<int>(designSeparator.getSize().y) -
                                    totalBulletsTextSize - 4};
    sf::Vector2f worldPosTotalBullets = window.mapPixelToCoords(posTotalBullets);
    totalBulletsIndicator.setPosition(worldPosTotalBullets);
    totalBulletsIndicator.setString(totalBulletsDisplayed);
    window.draw(remainingBulletsIndicator);
    window.draw(totalBulletsIndicator);
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

void Gui::updateMagazines(int remaining, int total, bool isInfinite) {
    if (remaining == 0)
        remainingBulletsIndicator.setFillColor(sf::Color(102, 0, 0, 200)); //red color
    else
        remainingBulletsIndicator.setFillColor(sf::Color(210, 210, 210, 200)); //standard color (grey)

    if (!isInfinite) {
        if ((total <= 20) && (total != 0))
            totalBulletsIndicator.setFillColor(sf::Color(255, 216, 0, 200)); //yellow color
        else if (total == 0)
            totalBulletsIndicator.setFillColor(sf::Color(102, 0, 0, 200)); //red color
    } else
        totalBulletsIndicator.setFillColor(sf::Color(210, 210, 210, 200)); //standard color (grey)

    std::string remainingBullets = std::to_string(remaining);
    this->remainingBulletsDisplayed = remainingBullets;
    if (isInfinite)
        this->totalBulletsDisplayed = "inf";
    else {
        std::string totalBullets = std::to_string(total);
        this->totalBulletsDisplayed = totalBullets;
    }
}

