//
// Created by alber on 25/10/2022.
//

#ifndef ELABORATO_MENUSTATE_H
#define ELABORATO_MENUSTATE_H

#include "GameState.h"
#include "GameException.h"

const int nButtons = 3;

class MenuState : public GameState {
private:
    sf::View view;

    void loadPlay();

    int nButtonSelected;
    unsigned int fontSize = 50;
    sf::Font font;
    sf::Text mainMenu[nButtons];

public:
    explicit MenuState(Game *game);

    void moveUp();

    void moveDown();

    void select();

    void draw(float dt) const override;

    void update(float dt) override;

    void handleInput() override;
};


#endif //ELABORATO_MENUSTATE_H
