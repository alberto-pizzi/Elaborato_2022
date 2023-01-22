//
// Created by alber on 21/01/2023.
//

#include "AchievementManager.h"

AchievementManager *AchievementManager::instance = nullptr;

AchievementManager::AchievementManager(Subject *subject, const TextureManager &guiTexManager)
        : guiTextures(guiTexManager), subject(subject) {
    guiTextures = guiTexManager;

    //load font
    std::string textFontFile = "res/fonts/arial.ttf";
    try {
        if (!progressFont.loadFromFile(textFontFile))
            throw GameException("Error opening textFontFile file", textFontFile, false);
    } catch (GameException &e) {
        exit(1); //close all
    }

    //register observer
    std::cout << "Register Observer" << std::endl;
    subject->registerObserver(this);
    std::cout << "Registered Observer" << std::endl;
}

void AchievementManager::createAchievement(const std::string &name, std::string description, unsigned int target) {
    achievements[name] = std::unique_ptr<Achievement>(
            new Achievement(guiTextures.getTextureRef("box"), guiTextures.getTextureRef("trophy"), name,
                            std::move(description), target, progressFont));
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

void AchievementManager::createInstance(Subject *subject, const TextureManager &guiTexManager) {
    if (!instance)
        instance = new AchievementManager(subject, guiTexManager);
}

void AchievementManager::drawAchievements(sf::RenderWindow &window) {
    for (auto it = AchievementManager::getInstance()->achievements.begin();
         it != AchievementManager::getInstance()->achievements.end(); it++) {
        it->second->drawAchievement(window);
        /*
        it->second->setFont(progressTextFont);
        window.draw(it->second->getProgressText());
         */

    }
}
