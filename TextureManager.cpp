//
// Created by alber on 25/10/2022.
//

#include "TextureManager.h"
#include "GameException.h"

void TextureManager::loadTexture(std::string name, std::string fileName) {
    // Load the texture
    sf::Texture tex;
    try {
        if (!tex.loadFromFile(fileName))
            throw GameException("Error opening texture file", fileName, false);
    } catch (GameException &e) {
        exit(1); //close all
    }

    // Add it to the list of textures
    this->textures[name] = tex;
}

sf::Texture &TextureManager::getTextureRef(std::string name) {
    return this->textures[name];
}

TextureManager::TextureManager() = default;
