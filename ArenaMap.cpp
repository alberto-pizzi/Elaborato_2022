//
// Created by alber on 03/11/2022.
//

#include "ArenaMap.h"

bool ArenaMap::Tile::isTraversable(int tile) {
    std::vector<int> walkableTiles;


    return false;
}

ArenaMap::Tile::Tile(int tile) {
    this->tileNumber = tile;


}

void ArenaMap::createMap(int map) {
    enum maps {
        desert = 0
    };
    switch (map) {
        case desert:
            readFile.open("res/maps/desertMap.xml"); //FIXME add exception for correct reading
            //TODO implement it (here and in PlayState)
            fromXMLtoTilesMatrix(readFile, layerLine(readFile, "principal_floor"), maxRowTiles, maxColumnTiles);

            readFile.close();
            break;
    }

}

int ArenaMap::layerLine(std::ifstream &file, std::string layerName) {
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
    return countLayers;
}

void ArenaMap::fromXMLtoTilesMatrix(std::ifstream &file, int lastLineSkipped, int maxColumnTiles, int maxRowTiles) {
    int i = 0, skipCount = 0;
    std::string line, number;
    //restart reading
    file.clear();
    file.seekg(std::ios::beg);
    //start reading
    while ((getline(file, line)) && (skipCount < lastLineSkipped)) {
        skipCount++;
    }
    while ((getline(file, line)) && (i < maxRowTiles)) {
        std::stringstream ss(line);
        for (int j = 0; j < maxColumnTiles; j++) {
            getline(ss, number, ',');
            tiles.emplace_back(stoi(number));
        }
        i++;
    }
}

int ArenaMap::tilemapDimensions(std::ifstream &file, char whichDim) {
    int dimension = 0;
    std::string searchTag, line;
    if (whichDim == 'w')
        searchTag = "width=";
    else if (whichDim == 'h')
        searchTag = "height=";
    //restart reading
    file.clear();
    file.seekg(std::ios::beg);
    //start reading
    while (!file.eof()) {
        getline(file, line, '"');
        if (line.find(searchTag, 0) != std::string::npos) {
            file >> dimension;
            break;
        }
    }
    return dimension;
}

