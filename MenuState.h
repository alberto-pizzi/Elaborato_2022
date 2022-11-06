//
// Created by alber on 25/10/2022.
//

#ifndef ELABORATO_MENUSTATE_H
#define ELABORATO_MENUSTATE_H

#include "GameState.h"

const int nButtons = 3;

class MenuState : public GameState {
private:
    sf::View view;

    void loadPlay();

    int nButtonSelected;
    sf::Font font;
    sf::Text mainMenu[nButtons];

public:
    explicit MenuState(Game *game);

    void moveUp();

    void moveDown();

    void select();

    virtual void draw(float dt);

    virtual void update(float dt);

    virtual void handleInput();
};


#endif //ELABORATO_MENUSTATE_H
