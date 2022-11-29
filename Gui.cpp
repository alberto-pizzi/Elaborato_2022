//
// Created by alber on 29/11/2022.
//

#include "Gui.h"

Gui::Gui() {
    loadTextures();
    std::cout << "i'm GUI constructor" << std::endl;
    healthBar.setTexture(texManager.getTextureRef("healthBar"));


}

void Gui::loadTextures() {
    texManager.loadTexture("healthBar", "res/textures/progressbar.png");
}

void Gui::drawGui(sf::RenderWindow &window) {
    int posX = abs(5 * 32 - window.getSize().x) - 16;
    sf::Vector2f worldPos = window.mapPixelToCoords({posX, 16});
    healthBar.setPosition(worldPos);
    window.draw(healthBar); //draw
}

void Gui::updateHealthBar(int hp) {
    int totalHP = 20;
    healthBar.setTextureRect({0, 0, (5 * 32 * hp) / totalHP, 32});
}

TextureManager Gui::getTexManager() {
    return texManager;
}
