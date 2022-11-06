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

ArenaMap::Tile::Tile(int tile, int layerNumber, int map, TextureManager texManager) {
    //TODO initialize other attributes
    std::cout << "Sono il costruttore Tile" << std::endl;
    this->tileNumber = tile;
    this->layer = layerNumber;
    this->walkable = isWalkable(tile, layerNumber, map);
    this->tileSprite.setTexture(texManager.getTextureRef("desert"));
}

void ArenaMap::loadMap(int chosenMap) {


    std::cout << "sono in case desert" << std::endl;
    //readFile.open(this->mapList[desert]); //FIXME add exception for correct reading
    readFile.open(this->mapList[chosenMap], std::ios::in | std::ios::binary);
    if (!readFile)
        std::cerr << "errore file" << std::endl;
    else {
        std::cout << "apertura corretta" << std::endl;
        fromXMLtoTilesToMatrix(readFile, maxRowTiles, maxColumnTiles, desert);
        stampa();
    }
    readFile.close();
    //TODO implement it (here and in PlayState)
/*
            for (int i = 0; i < totalLayers(readFile); i++) {
                fromMatrixToLayerMapPos(i);
                addTexturesToTiles(i);
            }
*/
}

ArenaMap::~ArenaMap() {
}

ArenaMap::ArenaMap() {
    std::cout << "Sono il costruttore mappa" << std::endl;
}

ArenaMap::ArenaMap(int chosenMap) {
    std::cout << "Sono il costruttore mappa con parametro" << std::endl;
    loadMap(chosenMap);

}

void ArenaMap::fromXMLtoTilesToMatrix(std::ifstream &file, int maxJ, int maxI, int chosenMap) {
    int i = 0, p;
    std::string line, number;
    int totLayers = totalLayers(readFile);
    loadTextures(chosenMap);
    //restart reading
    file.clear();
    file.seekg(std::ios::beg);
    //start reading
    for (int countLayer = 0; countLayer < totLayers; countLayer++) {
        while ((getline(file, line)) && (i < maxI)) {
            std::stringstream ss(line);
            for (int j = 0; j < maxJ; j++) {
                getline(ss, number, ',');
                tiles.emplace_back(
                        Tile(std::stoi(number), countLayer + 1, chosenMap, texmgr)); //FIXME fix vector filling
            }
            i++;
        }
    }
}

int ArenaMap::totalLayers(std::ifstream &file) {
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

void ArenaMap::loadTextures(int chosenMap) {
    switch (chosenMap) {
        case desert:
            texmgr.loadTexture("desert", "res/textures/desertTiles32x32.png");
            break;
    }
}

void ArenaMap::stampa() {
    for (int i = 0; i < maxRowTiles; i++) {
        for (int j = 0, countX = 0; countX < maxColumnTiles; j++, countX++) {
            std::cout << tiles[i * maxColumnTiles + j].tileNumber << " ";
        }
        std::cout << std::endl;
    }
}

