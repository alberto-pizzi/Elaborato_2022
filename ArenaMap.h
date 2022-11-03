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
    Tile tile[maxRowTiles][maxColumnTiles]; //FIXME try to use STL
public:
    //TODO implement methods
    void createMap(int map);

    int nLayers(std::ifstream &file);

    int layerLine(std::ifstream &file);

    void fromXMLtoMatrix(std::ifstream &file);
};


#endif //ELABORATO_ARENAMAP_H
