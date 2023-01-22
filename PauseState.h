//
// Created by Alberto Pizzi on 30/12/22.
//

#ifndef ELABORATO_PAUSESTATE_H
#define ELABORATO_PAUSESTATE_H

#include "GameState.h"
#include "GameException.h"
#include "AchievementState.h"

const int nButtonsPause = 3;

class PauseState : public GameState {
private:
    sf::View view;
    const int nButtons = 3;
    int nButtonSelected;
    unsigned int fontSize = 50;
    sf::Font font;
    sf::Text mainMenu[nButtonsPause];


public:
    explicit PauseState(Game *game);

    void moveUp();

    void moveDown();

    void select();

    void draw(float dt) const override;

    void update(float dt) override;

    void handleInput() override;
};


#endif //ELABORATO_PAUSESTATE_H
