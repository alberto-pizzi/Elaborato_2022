//
// Created by alber on 25/10/2022.
//

#ifndef ELABORATO_MENUSTATE_H
#define ELABORATO_MENUSTATE_H

#include "GameState.h"
#include "GameException.h"
#include "TextureManager.h"

const int nButtons = 3;

class MenuState : public GameState {
private:
    enum NameButton {
        //these numbers are related with nButtons
        Play = 0,
        Stats = 1,
        Exit = 2,
    };
    sf::View view;

    void loadPlay();

    int nButtonSelected;
    unsigned int fontSize = 24;
    const float buttonDistance = 64;
    const float alignValue = 8;
    const sf::Color selectedColor = sf::Color(102, 0, 0);
    const sf::Vector2i characterTextureSize = {32, 32};
    sf::Font font;
    sf::Text textMenu[nButtons];
    sf::Sprite menuButton[nButtons];

    sf::Sprite rightCharacter;
    sf::Sprite leftCharacter;

    TextureManager textureManager;

public:
    explicit MenuState(Game *game);

    void moveUp();

    void moveDown();

    void select();

    void draw(float dt) const override;

    void update(float dt) override;

    void handleInput() override;

    void loadTextures();
};


#endif //ELABORATO_MENUSTATE_H
