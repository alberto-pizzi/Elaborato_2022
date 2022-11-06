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
    //std::cout << "Sono il costruttore Tile" << std::endl;
    this->tileNumber = tile;
    this->layer = layerNumber;
    //this->walkable = isWalkable(tile, layerNumber, map);
    this->walkable = true;
    //this->tileSprite.setTexture(texManager.getTextureRef("desert"));
}

void ArenaMap::loadMap(int chosenMap) {


    std::cout << "sono in case desert" << std::endl;
    //readFile.open(this->mapList[desert]); //FIXME add exception for correct reading

    std::cout << "apertura corretta" << std::endl;
    fromXMLtoTilesToMatrix(maxColumnTiles, maxRowTiles, chosenMap);
    std::cout << "PRESTAMPA" << std::endl;
    stampa(6);

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

void ArenaMap::fromXMLtoTilesToMatrix(int maxJ, int maxI, int chosenMap) {
    int i = 0, openingLines = 6, closingLines = 4;

    std::ifstream file;
    file.open(this->mapList[chosenMap]);
    if (!file) {
        //TODO Error message
    } else {
        //int totLayers = totalLayers(readFile);
        int totLayers = 6;
        bool beginFile = true;
        std::string line, number;
        //load textures' map
        loadTextures(chosenMap);
        //restart reading
        file.clear();
        file.seekg(std::ios::beg);
        //skip initial XML lines
        if (beginFile) {
            for (int skipLines = 0; skipLines < openingLines; skipLines++)
                getline(file, line);
            beginFile = false;
        }
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
            i = 0;
            for (int skipLines = 0; skipLines < (closingLines - 1); skipLines++)
                getline(file, line);
        }
        file.close();
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

void ArenaMap::stampa(int totLayers) {
    for (int i = 0; i < maxRowTiles * totLayers; i++) {
        for (int j = 0, countX = 0; countX < maxColumnTiles * totLayers; j++, countX++) {
            std::cout << tiles[i * maxColumnTiles + j].tileNumber << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "TOTALE: " << tiles.size() << std::endl;
}

