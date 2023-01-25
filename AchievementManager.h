//
// Created by alber on 21/01/2023.
//

#ifndef ELABORATO_ACHIEVEMENTMANAGER_H
#define ELABORATO_ACHIEVEMENTMANAGER_H


#include "Observer.h"
#include "Subject.h"
#include "Achievement.h"
#include <map>
#include <memory>
#include <fstream>
#include "TextureManager.h"


class AchievementManager : public Observer {
private:
    Subject *subject;

    //textures
    TextureManager guiTextures;

    //achievements file
    std::string fileName = "res/achievements/achievements.txt";

    //fonts
    sf::Font progressFont;

    //instance
    static AchievementManager *instance;

    AchievementManager(Subject *subject, const TextureManager &guiTexManager);

public:
    std::map<std::string, std::unique_ptr<Achievement>> achievements;

    virtual ~AchievementManager();

    void createAchievement(const std::string &name, std::string description, unsigned int target);

    void saveAchievements();

    void loadAchievements();

    static void drawAchievements(sf::RenderWindow &window);

    void update(std::string achievementName, unsigned int value) override;

    static AchievementManager *getInstance();

    static void createInstance(Subject *subject, const TextureManager &guiTexManager);


};


#endif //ELABORATO_ACHIEVEMENTMANAGER_H
