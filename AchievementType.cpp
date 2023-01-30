//
// Created by alber on 21/01/2023.
//

#include "AchievementType.h"

float AchievementType::Achievement::previousBoxPosY = 0; //it is a temporary initialization. it will be as half window size thanks to AchievementState constructor
bool AchievementType::Achievement::firstTime = true;

AchievementType::Achievement::Achievement(const sf::Texture &boxTex, const sf::Texture &trophyTex,
                                          const std::string &name,
                                          unsigned int goal,
                                          const sf::Font &font)
        : name(name),
          targetProgress(goal), progressTextFont(font) {

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


}

void AchievementType::Achievement::drawAchievement(sf::RenderWindow &window) {


    if (firstTime) {
        previousBoxPosY = static_cast<float>(window.getSize().y) / 2.f;
        firstTime = false;
    }

    if (!posAlreadySet) {
        sf::Vector2i boxPos = {
                static_cast<int>(static_cast<float>(window.getSize().x) / 2.f - boxSprite.getGlobalBounds().width / 2),
                static_cast<int>(previousBoxPosY + borderDistance.y)};
        sf::Vector2f worldBoxPos = window.mapPixelToCoords(boxPos);
        boxSprite.setPosition(worldBoxPos);
        previousBoxPosY = boxPos.y + boxSprite.getGlobalBounds().height;
        posAlreadySet = true;
    }
    window.draw(boxSprite);

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

bool AchievementType::Achievement::isAchieved() {
    if (actualProgress >= targetProgress) {
        actualProgress = targetProgress;
        return true;
    } else
        return false;
}

void AchievementType::Achievement::update(unsigned int value) {
    //update progress
    actualProgress = value;

    if (!achieved) {

        std::string actualProgressString = std::to_string(actualProgress);
        std::string goalProgressString = std::to_string(targetProgress);
        progress = actualProgressString + " / " + goalProgressString;
        progressText.setString(progress);

        //update progress bar
        progressBar.setSize(sf::Vector2f(
                (static_cast<float>(actualProgress) * shadowProgressBar.getSize().x) /
                static_cast<float>(targetProgress),
                shadowProgressBar.getSize().y));
    }

    if (isAchieved()) {
        achieved = true;
        progressText.setFillColor(achievedBarColor);
        trophySprite.setColor(sf::Color::White);
        progressBar.setFillColor(sf::Color::Green);
    }

}

const sf::Sprite &AchievementType::Achievement::getBoxSprite() const {
    return boxSprite;
}

const std::string &AchievementType::Achievement::getName() const {
    return name;
}

unsigned int AchievementType::Achievement::getActualProgress() const {
    return actualProgress;
}

unsigned int AchievementType::Achievement::getTargetProgress() const {
    return targetProgress;
}

AchievementType::AchievementType(const sf::Texture &boxTex, const sf::Texture &trophyTex, const std::string &name,
                                 unsigned int goal, const sf::Font &font, int achievementType) : achievementType(
        achievementType), boxTexture(boxTex), trophyTexture(trophyTex), font(font) {

    createAchievement(name, goal);
}

void AchievementType::createAchievement(const std::string &name, unsigned int goal) {
    achievements.emplace_back(new Achievement(boxTexture, trophyTexture, name, goal, font));
}

void AchievementType::drawAchievements(sf::RenderWindow &window) {
    for (int i = 0; i < achievements.size(); i++) {
        achievements[i]->drawAchievement(window);
    }
}

int AchievementType::getAchievementType() const {
    return achievementType;
}

void AchievementType::update(unsigned int value) {
    for (int i = 0; i < achievements.size(); i++)
        achievements[i]->update(value);
}

const std::vector<std::unique_ptr<AchievementType::Achievement>> &AchievementType::getAchievements() const {
    return achievements;
}

