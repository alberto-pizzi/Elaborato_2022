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
            if (nLayers(readFile) == 0) {
                //TODO error message (no layers found)
            } else {
                //TODO write code
            }
            readFile.close();
            break;
    }

}

int ArenaMap::nLayers(std::ifstream &file) {
    int count = 0;
    std::string tag = "</layer>";
    //TODO implement it
}

void ArenaMap::fromXMLtoMatrix(std::ifstream &file) {
    //FIXME check if file was been reading correctly
    int i = 0;
    std::string line, number;
    while ((getline(file, line)) && (i < maxRowTiles)) {
        std::stringstream ss(line);
        for (int j = 0; j < maxColumnTiles; j++) {
            getline(ss, number, ',');
            tile[i][j] = stoi(number);
        }
        i++;
    }
}

int ArenaMap::layerLine(std::ifstream &file) {

}
