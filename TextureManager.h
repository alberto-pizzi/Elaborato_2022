//
// Created by alber on 25/10/2022.
//

#ifndef ELABORATO_TEXTUREMANAGER_H
#define ELABORATO_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager {
private:
    // Array of textures used
    std::map<std::string, sf::Texture> textures;
public:
    TextureManager();

    void loadTexture(std::string name, std::string fileName);

    sf::Texture &getTextureRef(std::string name);
};


#endif //ELABORATO_TEXTUREMANAGER_H
