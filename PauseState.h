//
// Created by Alberto Pizzi on 30/12/22.
//

#ifndef ELABORATO_PAUSESTATE_H
#define ELABORATO_PAUSESTATE_H

#include "GameState.h"
#include "GameException.h"
#include "AchievementState.h"
#include "TextureManager.h"

const int nButtonsPause = 3;

class PauseState : public GameState {
private:
    enum NameButton {
        //these numbers are related with nButtons
        Resume = 0,
        Achievements = 1,
        Exit = 2,
    };

    sf::View view;

    //texts
    int nButtonSelected;
    const int nButtons = 3;
    const unsigned int fontSize = 24;
    const unsigned int titleFontSize = 64;
    const float buttonDistance = 64;
    const float alignValue = 8;
    const sf::Color selectedColor = sf::Color(102, 0, 0);
    sf::Font font;
    sf::Text textMenu[nButtonsPause];
    sf::Text pauseMenu;

    //sprites
    sf::Sprite menuButton[nButtonsPause];
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
