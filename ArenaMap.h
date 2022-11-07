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
    std::ifstream readFile;
    TextureManager texmgr;
    sf::Texture tileSheet;
public:
    class Tile {
    public:
        bool walkable;
        sf::Vector2f posTile;
        int tileNumber;

        sf::Sprite tileSprite;

        explicit Tile(int tile, int map, int layerNumber, TextureManager texManager, int width, int height, int posX,
                      int posY);

        bool isWalkable(int tile, int layerNumber, int chosenMap);
    };

protected:
    struct Map {
        std::string nameFile;
        int totLayers;
        int width;
        int height;
    };

    //TODO insert game view
    int maxRowTiles = 45; //FIXME replace with method
    int maxColumnTiles = 90;
    std::vector<std::vector<std::vector<Tile>>> layers;
    //WARNING: update this struct array and enum for adding other Map
    Map mapList[1] = {
            {"res/maps/desertMap.xml", 6, 1280, 832},
    };
public:
    explicit ArenaMap(int chosenMap);

    virtual ~ArenaMap();

    bool loadMap(int chosenMap);

    bool fromXMLtoTilesToMatrix(int maxJ, int maxI, int chosenMap);

    void loadTextures(int chosenMap);

    void print3DVector(int totLayers); //TODO remove it (only for debug)

    void drawMap(sf::RenderWindow &window);
};


#endif //ELABORATO_ARENAMAP_H
