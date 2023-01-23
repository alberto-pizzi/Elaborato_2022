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
    sf::Font font;

    //colors
    const sf::Color backgroundColor = sf::Color(79, 79, 79);

    //view
    sf::View achievementView;
    const float scrollMove = 10;

public:
    explicit AchievementState(Game *game);

    void moveUp();

    void moveDown();

    void draw(float dt) const override;

    void update(float dt) override;

    void handleInput() override;
};


#endif //ELABORATO_ACHIEVEMENTSTATE_H
