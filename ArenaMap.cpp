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
            if (layerLine(readFile) == 0) {
                //TODO error message (no layers found) / exceptions
            } else {
                //TODO write code
            }
            readFile.close();
            break;
    }

}

int ArenaMap::layerLine(std::ifstream &file, std::string layerName) {
    //FIXME implement tagID for fast research
    int countLayers = 0;
    std::string tag = "name=";
    std::string searchTag = tag + '"' + layerName + '"';
    std::string line;
    //restart reading
    file.clear();
    file.seekg(std::ios::beg);
    //start reading
    while (!file.eof()) {
        countLayers++;
        getline(file, line);
        if (line.find(searchTag, 0) != std::string::npos)
            break;
    }
    //this method return the first line to start reading map
    return countLayers + 1;
}

void ArenaMap::fromXMLtoTilesMatrix(std::ifstream &file) {
    //FIXME implement skipping loop and fix this method for xml formatting (spaces...)
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

