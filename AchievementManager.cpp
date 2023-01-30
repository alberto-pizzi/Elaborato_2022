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
    subject->registerObserver(this);
}

void AchievementManager::createAchievement(int achievementType, const std::string &name, unsigned int target) {
    if (achievements.count(achievementType) > 0) {
        achievements[achievementType]->createAchievement(name, target);

    } else {
        achievements[achievementType] = std::unique_ptr<AchievementType>(
                new AchievementType(guiTextures.getTextureRef("box"), guiTextures.getTextureRef("trophy"), name,
                                    target,
                                    progressFont, achievementType));
    }
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
    unsigned int totalAchievements = 0;
    for (int i = 0; i < achievements.size(); i++)
        totalAchievements += achievements[i]->getAchievements().size();
    achievementFile << totalAchievements << std::endl;

    for (auto it = achievements.begin(); it != achievements.end(); it++) {
        for (int i = 0; i < it->second->getAchievements().size(); i++) {
            achievementFile << it->second->getAchievementType() << std::endl;
            achievementFile << it->second->getAchievements()[i]->getName() << std::endl;
            achievementFile << it->second->getAchievements()[i]->getActualProgress() << std::endl;
            achievementFile << it->second->getAchievements()[i]->getTargetProgress() << std::endl;
        }
    }

    achievementFile.close();

}

void AchievementManager::update(int achievementType, unsigned int value) {
    achievements[achievementType]->update(value);
}

AchievementManager::~AchievementManager() {
    subject->removeObserver(this);
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
        it->second->drawAchievements(window);
    }
}

