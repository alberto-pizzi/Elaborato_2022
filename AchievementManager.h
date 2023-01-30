//
// Created by alber on 21/01/2023.
//

#ifndef ELABORATO_ACHIEVEMENTMANAGER_H
#define ELABORATO_ACHIEVEMENTMANAGER_H

#include <map>
#include <memory>
#include <fstream>

#include "Observer.h"
#include "Subject.h"
#include "AchievementType.h"
#include "TextureManager.h"

//achievements file
const std::string achievementFileName = "res/achievements/achievements.txt";

class AchievementManager : public Observer {
private:
    Subject *subject;

    //textures
    TextureManager guiTextures;

    //fonts
    sf::Font progressFont;

    //instance
    static AchievementManager *instance;

    AchievementManager(Subject *subject, const TextureManager &guiTexManager);

public:
    //achievements from current game
    std::map<int, std::unique_ptr<AchievementType>> achievements;

    virtual ~AchievementManager();

    void createAchievement(int achievementType, const std::string &name, unsigned int target);

    void saveAchievements();

    static void drawAchievements(sf::RenderWindow &window);

    void update(int achievementType, unsigned int value) override;

    static AchievementManager *getInstance();

    static void createInstance(Subject *subject, const TextureManager &guiTexManager);

};


#endif //ELABORATO_ACHIEVEMENTMANAGER_H
