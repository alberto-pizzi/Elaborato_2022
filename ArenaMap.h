//
// Created by alber on 03/11/2022.
//

#ifndef ELABORATO_ARENAMAP_H
#define ELABORATO_ARENAMAP_H

#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "PosEntity.h"

enum maps {
    desert = 0
};

class ArenaMap {
private:
    std::ifstream readFile;

    class Tile {
    public:
        bool walkable;
        int posTileX;
        int posTileY;
        int tileNumber;
        int layer;
        sf::Texture texture;
        sf::Sprite sprite;

        explicit Tile(int tile, int layerNumber, int map);

        bool isWalkable(int tile, int layerNumber, int chosenMap);
    };

protected:
    //TODO insert game view
    int maxRowTiles = tilemapDimensions(readFile, 'h');
    int maxColumnTiles = tilemapDimensions(readFile, 'w');
    std::unique_ptr<PosEntity> posEntity;
    std::vector<Tile> tiles; //matrix in the form of a vector
    //WARNING: update this array and enum for adding other maps
    std::string map[1] = {
            "res/maps/desertMap.xml"
    };
public:
    void createMap(int chosenMap);

    int layerLine(std::ifstream &file, std::string layerName);

    int countLayers(std::ifstream &file);

    void fromXMLtoTilesMatrix(std::ifstream &file, int maxJ, int maxI, int chosenMap);

    int tilemapDimensions(std::ifstream &file, char whichDim);

    void drawMap();
};


#endif //ELABORATO_ARENAMAP_H
