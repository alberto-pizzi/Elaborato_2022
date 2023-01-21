//
// Created by alber on 21/01/2023.
//

#include "AchievementManager.h"

AchievementManager::AchievementManager(Subject *subject, const sf::Texture &boxTex, const sf::Texture &trophyTex)
        : boxTexture(boxTex), trophyTexture(trophyTex), subject(subject) {
    this->subject->registerObserver(this);
}

void AchievementManager::createAchievement(const std::string &name, std::string description, unsigned int target) {
    achievements[name] = std::unique_ptr<Achievement>(
            new Achievement(boxTexture, trophyTexture, name, std::move(description), target));
}

void AchievementManager::saveAchievements() {

}

void AchievementManager::update(std::string achievementName, unsigned int value) {
    achievements[achievementName]->update(value);
}

AchievementManager::~AchievementManager() {
    //subject->removeObserver(this);
}
