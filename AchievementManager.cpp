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
    std::ofstream achievementFile;

    achievementFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        achievementFile.open(fileName);
    }
    catch (std::ios_base::failure &e) {
        throw GameException("Error opening achievement file", fileName, false);
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
        /*
        it->second->setFont(progressTextFont);
        window.draw(it->second->getProgressText());
         */

    }
}

void AchievementManager::loadAchievements() {
    std::ifstream achievementFile;

    achievementFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        achievementFile.open(fileName);
    }
    catch (std::ios_base::failure &e) {
        throw GameException("Error opening achievement file", fileName, false);
    }

    int totalAchievements;
    std::string achievementName, actualProgress, target, totalAchievementsString;

    //read total achievements
    std::getline(achievementFile, totalAchievementsString);
    totalAchievements = std::stoi(totalAchievementsString);

    //init map
    achievements.clear();

    //read each achievement
    for (int i = 0; i < totalAchievements; i++) {
        std::getline(achievementFile, achievementName);
        std::getline(achievementFile, actualProgress);
        std::getline(achievementFile, target);
        achievements[achievementName]->setName(achievementName);
        achievements[achievementName]->setActualProgress(std::stoul(actualProgress));
        achievements[achievementName]->setTargetProgress(std::stoul(target));
    }

    achievementFile.close();
}
