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
        Achievements = 1,
        Exit = 2,
    };
    sf::View view;

    void loadPlay();

    //texts
    int nButtonSelected;
    unsigned int fontSize = 18;
    const float buttonDistance = 64;
    const float alignValue = 6;
    //const sf::Color selectedColor = sf::Color(102, 0, 0);
    const sf::Color selectedColor = sf::Color::Yellow;
    sf::Font font;
    sf::Text textMenu[nButtons];


    //sprites
    const sf::Vector2i characterTextureSize = {32, 32};
    sf::Sprite menuButton[nButtons];
    sf::Sprite rightCharacter;
    sf::Sprite leftCharacter;
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
