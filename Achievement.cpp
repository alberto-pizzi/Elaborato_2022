//
// Created by alber on 21/01/2023.
//

#include "Achievement.h"

float Achievement::previousBoxPosY = 0; //it is a temporary initialization. it will be as half window size thanks to AchievementState constructor

Achievement::Achievement(const sf::Texture &boxTex, const sf::Texture &trophyTex, const std::string &name,
                         const std::string &description,
                         unsigned int goal, const sf::Font &font)
        : name(name), description(description),
          targetProgress(goal), progressTextFont(font) {

    //FIXME

    std::string actualProgressString = std::to_string(actualProgress);
    std::string goalProgressString = std::to_string(goal);

    progress = actualProgressString + " / " + goalProgressString;

    boxSprite.setTexture(boxTex);
    trophySprite.setTexture(trophyTex);

    if (isAchieved())
        achieved = true;

    //shadow bar
    shadowProgressBar.setSize(
            sf::Vector2f(static_cast<float>(boxTex.getSize().x) / 2.f, static_cast<float>(boxTex.getSize().y) / 4.f));
    shadowProgressBar.setFillColor(sf::Color::Black);

    //progress bar
    progressBar.setFillColor(barColor);
    progressBar.setOutlineThickness(2);
    progressBar.setOutlineColor(sf::Color::Black);
    progressBar.setSize(sf::Vector2f(
            (static_cast<float>(actualProgress) * shadowProgressBar.getSize().x) / static_cast<float>(targetProgress),
            shadowProgressBar.getSize().y));

    //progress bar text
    progressText.setCharacterSize(barTextFontSize);
    progressText.setFillColor(sf::Color::White);
    progressText.setFont(progressTextFont);
    progressText.setString(progress);

    //title text
    achievementNameText.setCharacterSize(barTextFontSize);
    achievementNameText.setFillColor(sf::Color::Black);
    achievementNameText.setStyle(sf::Text::Bold);
    achievementNameText.setFont(progressTextFont);
    achievementNameText.setString(this->name);

    //trophy
    trophySprite.setScale(sf::Vector2f(2, 2));
    trophySprite.setColor(tarnishColor);








    //boxSprite.setScale(sf::Vector2f(1.5,1.5));

}

void Achievement::drawAchievement(sf::RenderWindow &window) {

    //static_cast<float>(window.getSize().y)/2.f - boxSprite.getGlobalBounds().height/2
    //box
    /*
    sf::Vector2f boxPos = {static_cast<float>(window.getSize().x)/2.f - boxSprite.getGlobalBounds().width/2,
                           previousBoxPosY + borderDistance.y};
                           */
    if (firstTime) {
        sf::Vector2i boxPos = {static_cast<int>((window.getSize().x) / 2.f - boxSprite.getGlobalBounds().width / 2),
                               static_cast<int>(previousBoxPosY + borderDistance.y)};
        sf::Vector2f worldBoxPos = window.mapPixelToCoords(boxPos);
        boxSprite.setPosition(worldBoxPos);
        firstTime = false;
    }
    window.draw(boxSprite);

    //update previousBoxBounds
    if (!posAlreadySet) {
        previousBoxPosY = boxSprite.getPosition().y + boxSprite.getGlobalBounds().height;
        posAlreadySet = true;
    }

    //progress bar
    sf::Vector2f barPos = {boxSprite.getPosition().x + borderDistance.x,
                           boxSprite.getPosition().y + boxSprite.getGlobalBounds().height -
                           shadowProgressBar.getGlobalBounds().height - borderDistance.y};
    progressBar.setPosition(barPos);
    shadowProgressBar.setPosition(barPos);
    window.draw(shadowProgressBar);
    window.draw(progressBar);

    //progress bar text
    sf::Vector2f barTextPos = {
            barPos.x + shadowProgressBar.getGlobalBounds().width / 2.f - progressText.getGlobalBounds().width / 2.f,
            barPos.y + shadowProgressBar.getGlobalBounds().height / 2.f - progressText.getGlobalBounds().height / 2.f -
            1};
    progressText.setPosition(barTextPos);
    window.draw(progressText);

    //achievement name
    sf::Vector2f achievementPos = {boxSprite.getPosition().x + borderDistance.x,
                                   boxSprite.getPosition().y + borderDistance.y};
    achievementNameText.setPosition(achievementPos);
    window.draw(achievementNameText);


    //trophy
    sf::Vector2f trophyPos = {boxSprite.getPosition().x + boxSprite.getGlobalBounds().width - borderDistance.x -
                              trophySprite.getGlobalBounds().width, achievementPos.y};
    trophySprite.setPosition(trophyPos);

    window.draw(trophySprite);
}

bool Achievement::isAchieved() {
    if (actualProgress >= targetProgress) {
        actualProgress = targetProgress;
        return true;
    } else
        return false;
}

void Achievement::update(unsigned int value) {
    //update progress
    actualProgress = value;

    if (isAchieved()) {
        achieved = true;
        progressText.setFillColor(achievedBarColor);
        trophySprite.setColor(sf::Color::White);
    }

    std::string actualProgressString = std::to_string(actualProgress);
    std::string goalProgressString = std::to_string(targetProgress);
    progress = actualProgressString + " / " + goalProgressString;
    progressText.setString(progress);

    //update progress bar
    progressBar.setSize(sf::Vector2f(
            (static_cast<float>(actualProgress) * shadowProgressBar.getSize().x) / static_cast<float>(targetProgress),
            shadowProgressBar.getSize().y));
}

unsigned int Achievement::getActualProgress() const {
    return actualProgress;
}

const sf::Sprite &Achievement::getBoxSprite() const {
    return boxSprite;
}

const sf::Sprite &Achievement::getTrophySprite() const {
    return trophySprite;
}

const std::string &Achievement::getProgress() const {
    return progress;
}

float Achievement::getPreviousBoxPosY() {
    return previousBoxPosY;
}

void Achievement::setPreviousBoxPosY(float previousBoxPosY) {
    Achievement::previousBoxPosY = previousBoxPosY;
}

