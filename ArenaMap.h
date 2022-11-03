//
// Created by alber on 03/11/2022.
//

#ifndef ELABORATO_ARENAMAP_H
#define ELABORATO_ARENAMAP_H

#include <memory>
#include <fstream>

#include "PosEntity.h"

class ArenaMap {
protected:
    int maxWidth;
    int maxHeight;
    std::unique_ptr<PosEntity> posEntity;
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

public:
    //TODO implement methods
    void createMap(int map);
};


#endif //ELABORATO_ARENAMAP_H
