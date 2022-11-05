//
// Created by alber on 25/10/2022.
//

#include "TextureManager.h"


void TextureManager::loadTexture(std::string name, std::string fileName) {
    // Load the texture
    sf::Texture tex;
    tex.loadFromFile(fileName);

    // Add it to the list of textures
    this->textures[name] = tex;
}

sf::Texture &TextureManager::getTextureRef(std::string name) {
    return this->textures[name];
}

TextureManager::TextureManager() = default;
