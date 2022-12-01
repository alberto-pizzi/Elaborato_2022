//
// Created by alber on 29/11/2022.
//

#ifndef ELABORATO_GUI_H
#define ELABORATO_GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "TextureManager.h"

class Gui {
private:
    void loadTextures();

    TextureManager texManager;
    sf::Sprite healthBar;
public:
    const sf::Sprite &getHealthBar() const;

public:
    Gui();

    void message(std::string message);

    void updateHealthBar(int hp);

    void updateArmor(int armor);

    void drawGui(sf::RenderWindow &window);

    TextureManager getTexManager();

};


#endif //ELABORATO_GUI_H
