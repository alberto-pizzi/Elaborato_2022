//
// Created by alber on 22/01/2023.
//

#ifndef ELABORATO_ACHIEVEMENTSTATE_H
#define ELABORATO_ACHIEVEMENTSTATE_H


#include <memory>
#include <SFML/Window/Event.hpp>

#include "GameState.h"
#include "GameException.h"
#include "AchievementManager.h"


class AchievementState : public GameState {
private:
    sf::Font font;

    //colors
    const sf::Color backgroundColor = sf::Color(79, 79, 79);

    //textures
    TextureManager achievementsTextures;

    //font
    sf::Font progressFont;

    //view
    sf::View achievementView;
    const float scrollMove = 50;

    //achievements from file
    std::map<int, std::unique_ptr<AchievementType>> achievements;
public:
    explicit AchievementState(Game *game);

    void loadTextures();

    void loadAchievements();

    void drawAchievementsFromFile() const;

    void draw(float dt) const override;

    void update(float dt) override;

    void handleInput() override;
};


#endif //ELABORATO_ACHIEVEMENTSTATE_H
