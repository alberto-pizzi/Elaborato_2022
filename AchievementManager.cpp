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
            new Achievement(guiTextures.getTextureRef("box"), guiTextures.getTextureRef("trophy"), name, target,
                            progressFont));
}

void AchievementManager::saveAchievements() {
    std::ofstream achievementFile;

    achievementFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        achievementFile.open(achievementFileName);
    }
    catch (std::ios_base::failure &e) {
        throw GameException("Error opening achievement file", achievementFileName, false);
    }

    //write total achievements
    achievementFile << achievements.size() << std::endl;

    for (auto it = achievements.begin(); it != achievements.end(); it++) {
        achievementFile << it->second->getName() << std::endl;
        achievementFile << it->second->getActualProgress() << std::endl;
        achievementFile << it->second->getTargetProgress() << std::endl;
    }

    achievementFile.close();


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
    }
}

