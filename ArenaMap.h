//
// Created by alber on 03/11/2022.
//

#ifndef ELABORATO_ARENAMAP_H
#define ELABORATO_ARENAMAP_H

#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "PosEntity.h"
#include "TextureManager.h"

enum maps {
    desert = 0,
};

class ArenaMap {
private:
    std::ifstream readFile;
    TextureManager texmgr;
    sf::Texture tileSheet;

    class Tile {
    public:
        bool walkable;
        sf::Vector2f posTile;
        int tileNumber;
        int layer;

        sf::Sprite tileSprite;

        explicit Tile(int tile, int layerNumber, int map, TextureManager texManager);

        bool isWalkable(int tile, int layerNumber, int chosenMap);
    };

protected:
    //TODO insert game view
    int maxRowTiles = 45; //FIXME replace with method
    int maxColumnTiles = 90;
    int totalTiles = maxRowTiles * maxColumnTiles;
    std::vector<Tile> tiles; //matrix in the form of a vector
    //WARNING: update this array and enum for adding other map
    struct map {
        std::string namefile;
        int totLayers;
    };
    map mapList[1] = {
            {"res/map/desertMap.xml", 6},
    };
public:
    explicit ArenaMap(int chosenMap);

    virtual ~ArenaMap();

    bool loadMap(int chosenMap);

    bool fromXMLtoTilesToMatrix(int maxJ, int maxI, int chosenMap);

    void loadTextures(int chosenMap);

    void stampa(int totLayers);


};


#endif //ELABORATO_ARENAMAP_H
