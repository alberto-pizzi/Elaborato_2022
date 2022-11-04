//
// Created by alber on 03/11/2022.
//

#ifndef ELABORATO_ARENAMAP_H
#define ELABORATO_ARENAMAP_H

#include <memory>
#include <fstream>
#include <sstream>
#include <string>

#include "PosEntity.h"

//WARNING: this values need to be updated when the overall tile size is changed (in XML)
//FIXME remove const and implement a method for read width and height from xml (using STL for matrix)
const int maxColumnTiles = 90;
const int maxRowTiles = 45;

class ArenaMap {

private:
    std::ifstream readFile;

    class Tile {
    public:
        Tile(bool walkable);

        bool walkable;
        int posTileX;
        int posTileY;

        //TODO implement it
        bool isTraversable();
    };

protected:
    //TODO insert game view
    int maxWidth;
    int maxHeight;
    std::unique_ptr<PosEntity> posEntity;
    Tile tile[maxRowTiles][maxColumnTiles];
public:
    //TODO implement methods
    void createMap(int map);

    int layerLine(std::ifstream &file, std::string layerName);

    void fromXMLtoTilesMatrix(std::ifstream &file, int lastLineSkipped);
};


#endif //ELABORATO_ARENAMAP_H
