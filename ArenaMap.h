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

enum mapNumber {
    desert = 0,
};

class ArenaMap {
private:
    TextureManager texmgr;

    class Tile {
    public:
        bool walkable;
        sf::Vector2f posTile;
        int tileNumber;
        int layer;

        sf::Sprite tileSprite;

        Tile(int tile, const std::string &nameMap, int width, int height, int posX, int posY,
             const sf::Texture &texture,
             int layer);

        bool isWalkable(int tile, int layerNumber, int chosenMap); //FIXME
    };

protected:
    //TODO insert game view
    int maxColumnTiles;
    int maxRowTiles;
    int tileSizeX;
    int tileSizeY;
    int totalLayers;
    int widthFile;
    int heightFile;
    std::string nameFile;
    std::string nameMap;
    std::vector<Tile *> tileMap;
    //WARNING: update this struct array and enum for adding other Map
    std::string mapList[1] = {
            "res/maps/desertMap.txt",
    };
public:
    explicit ArenaMap(int chosenMap);

    virtual ~ArenaMap();

    bool loadMap(int chosenMap);

    bool loadMapFile(int maxJ, int maxI, int chosenMap);

    void print3DVector(); //TODO remove it (only for debug)

    void drawMap(sf::RenderWindow &window);
};


#endif //ELABORATO_ARENAMAP_H
