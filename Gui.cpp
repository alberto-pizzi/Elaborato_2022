//
// Created by alber on 29/11/2022.
//

#include "Gui.h"

Gui::Gui(unsigned int points, int round, int remainingBullets, int totalBullets, bool infiniteBullets,
         const sf::Texture &weaponTexture, const TextureManager &guiTexManager) : weaponTexture(weaponTexture) {
    guiTextures = guiTexManager;
    std::cout << "i'm GUI constructor" << std::endl;
    healthBar.setTexture(guiTextures.getTextureRef("healthBar"));

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
    updatePoints(points);
    //pointsDisplayed = std::to_string(points);

    //set round indicator
    roundIndicator.setFont(numbersOrTitlesFont);
    roundIndicator.setCharacterSize(titleFontSize);
    roundIndicator.setFillColor(redGuiColor);
    roundDisplayed = std::to_string(round);

    //set bullets indicator
    remainingBulletsIndicator.setFont(textFont);
    remainingBulletsIndicator.setCharacterSize(remainingBulletsTextSize);
    remainingBulletsIndicator.setFillColor(semiTransparentGreyGuiColor);
    //remainingBulletsDisplayed = "12 "; //this number must be equal to Mike's STARTING bullets
    remainingBulletsDisplayed = std::to_string(remainingBullets);

    totalBulletsIndicator.setFont(textFont);
    totalBulletsIndicator.setCharacterSize(totalBulletsTextSize);
    totalBulletsIndicator.setFillColor(semiTransparentGreyGuiColor);
    if (infiniteBullets)
        totalBulletsDisplayed = "inf";
    else
        totalBulletsDisplayed = std::to_string(totalBullets);

    designSeparator.setSize(sf::Vector2f(3, 60));
    designSeparator.setFillColor(semiTransparentGreyGuiColor);

    //weapon indicator

    weaponSpriteIndicator.setTexture(weaponTexture);
    weaponSpriteIndicator.setColor(sf::Color::Black);
    weaponSpriteIndicator.setScale(sf::Vector2f(1.5, 1.5));

}

void Gui::drawGui(sf::RenderWindow &window) {
    //draw HealthBar
    int posXHealth =
            static_cast<int>(window.getSize().x - guiTextures.getTextureRef("healthBar").getSize().x) -
            distanceFromWindowLimits.x;
    sf::Vector2f worldPosHealth = window.mapPixelToCoords({posXHealth, distanceFromWindowLimits.y});
    healthBar.setPosition(worldPosHealth);
    window.draw(healthBar);

    //draw PointsIndicator
    int posXPoints = static_cast<int>(window.getSize().x) / 2 - textFontSize * (totalDigits / 2 - 1);
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

    //draw weapon type
    sf::Vector2i posWeaponTypeIndicator = {static_cast<int>(static_cast<float>(window.getSize().x) -
                                                            (hitBoxWeaponSize.x * weaponSpriteIndicator.getScale().x)) -
                                           3 * distanceFromWindowLimits.x,
                                           static_cast<int>(static_cast<float>(window.getSize().y) -
                                                            (static_cast<float>(weaponSpriteIndicator.getTextureRect().height) *
                                                             weaponSpriteIndicator.getScale().y)) -
                                           distanceFromWindowLimits.y};
    sf::Vector2f worldPosWeaponTypeIndicator = window.mapPixelToCoords(posWeaponTypeIndicator);
    weaponSpriteIndicator.setPosition(worldPosWeaponTypeIndicator);
    window.draw(weaponSpriteIndicator);
}

void Gui::updateHealthBar(float hp) {
    float totalHP = 20; //this is to be equal to mike total HP
    healthBar.setTextureRect({0, 0, static_cast<int>((5 * 32 * hp) / totalHP), 32}); //these values are the texture size
}

TextureManager Gui::getTexManager() {
    return guiTextures;
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
            pointsDisplayed = zeros + digits;
        else {
            for (int i = 0; i < totalDigits - numDigits - 1; i++)
                zeros += "0";
            pointsDisplayed = zeros + digits;
        }
    } else
        pointsDisplayed = digits;
}

const std::string &Gui::getPointsDisplayed() const {
    return pointsDisplayed;
}

void Gui::updateRound(int round) {
    std::string roundString = std::to_string(round);
    roundDisplayed = roundString;
}

void Gui::updateMagazines(int remaining, int total, bool isInfinite) {
    if (remaining == 0)
        remainingBulletsIndicator.setFillColor(redGuiColor); //red color
    else
        remainingBulletsIndicator.setFillColor(semiTransparentGreyGuiColor); //standard color (grey)

    if (!isInfinite) {
        if ((total <= 20) && (total != 0))
            totalBulletsIndicator.setFillColor(yellowGuiColor); //yellow color
        else if (total == 0)
            totalBulletsIndicator.setFillColor(redGuiColor); //red color
    } else
        totalBulletsIndicator.setFillColor(semiTransparentGreyGuiColor); //standard color (grey)

    std::string remainingBullets = std::to_string(remaining);
    remainingBulletsDisplayed = remainingBullets;
    if (isInfinite)
        totalBulletsDisplayed = "inf";
    else {
        std::string totalBullets = std::to_string(total);
        totalBulletsDisplayed = totalBullets;
    }
}

void Gui::updateWeaponType(const sf::Texture &newWeaponTexture, const sf::IntRect &idleFrame,
                           const sf::Vector2f &hitboxSize) {
    weaponSpriteIndicator.setTexture(newWeaponTexture);
    weaponSpriteIndicator.setTextureRect(idleFrame);
    hitBoxWeaponSize = hitboxSize;
    weaponSpriteIndicator.setScale(sf::Vector2f(1.5, 1.5));
}

