//
// Created by alber on 03/11/2022.
//

#include "ArenaMap.h"

bool ArenaMap::Tile::isWalkable(int tile, int layerNumber, int chosenMap) {
    switch (chosenMap) {
        case desert:
            if ((layerNumber == 2) && (tile != 0)) {
                for (int i = 41; i <= 288; i++) {
                    if (tile == i)
                        return true;
                    else if (i == 48)
                        i = 200;
                    else if (i == 248)
                        i = 280;
                }
            }
            break;
    }
    return false;
}

ArenaMap::Tile::Tile(int tile, int layerNumber, int map) {
    //TODO initialize other attributes
    this->tileNumber = tile;
    this->layer = layerNumber;
    this->walkable = isWalkable(tile, layerNumber, map);
}

void ArenaMap::createMap(int chosenMap) {

    switch (chosenMap) {
        case desert:
            readFile.open(this->map[desert]); //FIXME add exception for correct reading
            //TODO implement it (here and in PlayState)
            fromXMLtoTilesMatrix(readFile, maxRowTiles, maxColumnTiles, desert);

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

void ArenaMap::fromXMLtoTilesMatrix(std::ifstream &file, int maxJ, int maxI, int chosenMap) {
    int i = 0;
    std::string line, number;
    int totalLayers = countLayers(readFile);
    //restart reading
    file.clear();
    file.seekg(std::ios::beg);
    //start reading
    for (int countLayer = 0; countLayer < totalLayers; countLayer++) {
        while ((getline(file, line)) && (i < maxI)) {
            std::stringstream ss(line);
            for (int j = 0; j < maxJ; j++) {
                getline(ss, number, ',');
                tiles.emplace_back(stoi(number), countLayer + 1, chosenMap);
            }
            i++;
        }
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

int ArenaMap::countLayers(std::ifstream &file) {
    int count = 0;
    std::string searchTag = "</layer>";
    std::string line;
    //restart reading
    file.clear();
    file.seekg(std::ios::beg);
    //start reading
    while (!file.eof()) {
        getline(file, line);
        if (line.find(searchTag, 0) != std::string::npos)
            count++;
    }
    return count;
}

void ArenaMap::drawMap() {
    int pixel = 32;


}

