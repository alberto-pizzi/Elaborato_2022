//
// Created by alber on 21/01/2023.
//

#include "AchievementManager.h"

AchievementManager *AchievementManager::instance = nullptr;

AchievementManager::AchievementManager(Subject *subject, const sf::Texture &boxTex, const sf::Texture &trophyTex)
        : boxTexture(boxTex), trophyTexture(trophyTex), subject(subject) {
    std::cout << "Register Observer" << std::endl;
    subject->registerObserver(this);
    std::cout << "Registered Observer" << std::endl;
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
    std::cout << "Remove Observer" << std::endl;
    subject->removeObserver(this);
    std::cout << "Removed Observer" << std::endl;
}

AchievementManager *AchievementManager::getInstance() {
    return instance;
}

void AchievementManager::createInstance(Subject *subject, const sf::Texture &boxTex, const sf::Texture &trophyTex) {
    if (!instance)
        instance = new AchievementManager(subject, boxTex, trophyTex);
}
