//
// Created by alber on 22/01/2023.
//

#ifndef ELABORATO_ACHIEVEMENTSTATE_H
#define ELABORATO_ACHIEVEMENTSTATE_H


#include "GameState.h"
#include "GameException.h"
#include <memory>
//#include <iterator>

//#include "Achievement.h"
#include "AchievementManager.h"


class AchievementState : public GameState {
private:
    sf::View view;

    int nButtonSelected;
    unsigned int fontSize = 50;
    sf::Font font;
    const int nButtons = 3;
    sf::Text mainMenu[3];
    //std::vector<std::unique_ptr<Achievement>> achievements;
    //AchievementManager* achievementManager;

    bool printed = false;

public:
    explicit AchievementState(Game *game);

    void moveUp();

    void moveDown();

    void select();

    void draw(float dt) const override;

    void update(float dt) override;

    void handleInput() override;
};


#endif //ELABORATO_ACHIEVEMENTSTATE_H
