//
// Created by alber on 03/11/2022.
//

#include "ArenaMap.h"

bool ArenaMap::Tile::isTraversable() {
    return false;
}

ArenaMap::Tile::Tile(bool walkable) {
    this->walkable = walkable;
}

void ArenaMap::createMap(int map) {
    enum maps {
        desert = 0
    };
    switch (map) {
        case desert:
            readFile.open(""); //FIXME add file
            //TODO implement
            readFile.close();
            break;
    }

}
