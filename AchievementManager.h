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


class AchievementManager : public Observer {
private:
    sf::Texture boxTexture;
    sf::Texture trophyTexture;


    Subject *subject;
public:
    std::map<std::string, std::unique_ptr<Achievement>> achievements;

    AchievementManager(Subject *subject, const sf::Texture &boxTex, const sf::Texture &trophyTex);

    virtual ~AchievementManager();

    void createAchievement(const std::string &name, std::string description, unsigned int target);

    void saveAchievements();

    void update(std::string achievementName, unsigned int value) override;


};


#endif //ELABORATO_ACHIEVEMENTMANAGER_H
