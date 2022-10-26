//
// Created by alber on 25/10/2022.
//

#ifndef ELABORATO_TEXTUREMANAGER_H
#define ELABORATO_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

//FIXME change array implementation to solve error OpenGL
class TextureManager {
private:

    // Array of textures used
    std::map<std::string, sf::Texture> textures;

public:
    TextureManager();

    // Add a texture from a file
    void loadTexture(const std::string &name, const std::string &filename);

    // Translate an id into a reference
    sf::Texture &getTextureRef(const std::string &texture);


};


#endif //ELABORATO_TEXTUREMANAGER_H
