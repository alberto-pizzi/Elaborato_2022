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

class ArenaMap {
private:
    std::ifstream readFile;

    class Tile {
    public:
        explicit Tile(int tile);
        bool walkable;
        int posTileX;
        int posTileY;
        int tileNumber;

        //TODO implement it
        bool isTraversable(int tile);
    };

protected:
    //TODO insert game view
    int maxRowTiles = tilemapDimensions(readFile, 'h');
    int maxColumnTiles = tilemapDimensions(readFile, 'w');
    std::unique_ptr<PosEntity> posEntity;
    std::vector<Tile> tiles; //matrix in the form of a vector
public:
    void createMap(int map);

    int layerLine(std::ifstream &file, std::string layerName);

    void fromXMLtoTilesMatrix(std::ifstream &file, int lastLineSkipped, int maxColumnTiles, int maxRowTiles);

    int tilemapDimensions(std::ifstream &file, char whichDim);
};


#endif //ELABORATO_ARENAMAP_H
