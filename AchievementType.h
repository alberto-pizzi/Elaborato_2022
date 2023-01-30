//
// Created by alber on 21/01/2023.
//

#ifndef ELABORATO_ACHIEVEMENTTYPE_H
#define ELABORATO_ACHIEVEMENTTYPE_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include "GameException.h"


enum AchievementTypes {
    Kills = 0, Collect_coins, Points,
};

class AchievementType {
private:

    class Achievement {

    private:
        //sprites
        sf::Sprite boxSprite;
        sf::Sprite trophySprite;

        //progress
        std::string name;
        unsigned int actualProgress = 0;
        unsigned int targetProgress;

        static float previousBoxPosY;
        bool posAlreadySet = false;
        static bool firstTime;

        //colors
        const sf::Color tarnishColor = sf::Color(47, 47, 47);
        const sf::Color barColor = sf::Color(99, 151, 208);
        const sf::Color achievedBarColor = sf::Color(8, 69, 126);

        //progress bar
        sf::RectangleShape progressBar;
        sf::RectangleShape shadowProgressBar;
        const sf::Vector2f borderDistance = {28, 28};
        sf::Font progressTextFont;
        std::string progress;
        sf::Text achievementNameText;
        int barTextFontSize = 20;
        sf::Text progressText;
        bool achieved = false;
    public:


        Achievement(const sf::Texture &boxTex, const sf::Texture &trophyTex, const std::string &name, unsigned int goal,
                    const sf::Font &font);

        bool isAchieved();

        void update(unsigned int value);

        void drawAchievement(sf::RenderWindow &window);

        const sf::Sprite &getBoxSprite() const;

        const std::string &getName() const;

        unsigned int getActualProgress() const;

        unsigned int getTargetProgress() const;
    };

    //textures
    sf::Texture boxTexture;
    sf::Texture trophyTexture;

    //fonts
    sf::Font font;

    //same type achievements
    int achievementType;
    std::vector<std::unique_ptr<Achievement>> achievements;
public:
    AchievementType(const sf::Texture &boxTex, const sf::Texture &trophyTex, const std::string &name, unsigned int goal,
                    const sf::Font &font, int achievementType);

    void drawAchievements(sf::RenderWindow &window);

    void update(unsigned int value);

    void createAchievement(const std::string &name, unsigned int goal);

    int getAchievementType() const;

    const std::vector<std::unique_ptr<Achievement>> &getAchievements() const;

};


#endif //ELABORATO_ACHIEVEMENTTYPE_H
