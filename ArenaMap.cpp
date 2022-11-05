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
    this->tileNumber = tile;
    this->layer = layerNumber;
    this->walkable = isWalkable(tile, layerNumber, map);
    this->tileSprite.setTexture(texManager.getTextureRef("desert"));
    addTexturesToTiles();
}

void ArenaMap::createMap(int chosenMap) {

    switch (chosenMap) {
        case desert:
            readFile.open(this->map[desert]); //FIXME add exception for correct reading
            //TODO implement it (here and in PlayState)
            fromXMLtoTilesMatrix(readFile, maxRowTiles, maxColumnTiles, desert);
            readFile.close();
            drawMap();
            break;
    }

}

int ArenaMap::layerStartVectorIndex(int layerNumber) {
    int vectorIndex = 0;
    for (int i = 0; i < tiles.size(); i++) {
        vectorIndex++;
        if (maxColumnTiles * maxRowTiles * (layerNumber - 1))
            break;
    }
    if (vectorIndex <= 1) { //vector index = 0
        vectorIndex = 0;
        return vectorIndex;
    } else
        return vectorIndex;
}

void ArenaMap::fromXMLtoTilesMatrix(std::ifstream &file, int maxJ, int maxI, int chosenMap) {
    int i = 0;
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
                tiles.emplace_back(stoi(number), countLayer + 1, chosenMap, texmgr);
            }
            i++;
        }
    }
}

int ArenaMap::tileMapDimensions(std::ifstream &file, char whichDim) {
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
            texmgr.loadTexture("desert", "res/textures/desertTiles32x32.jpg");
            break;
    }
}

sf::Sprite ArenaMap::drawMap() {

}

void ArenaMap::fromMatrixToLayerMap(int layerNumber) {
    float pixel = 32, countX, countY = 0;
    int startIndex = layerStartVectorIndex(layerNumber);

    for (int i = startIndex; i < maxRowTiles; i++) {
        countX = 0;
        for (int j = startIndex; j < maxColumnTiles; j++) {
            countX++;
            tiles[i * maxColumnTiles + j].posTile.x = countX * pixel * (float) tiles[i * maxColumnTiles + j].tileNumber;
        }

        countY++;
        tiles[i * maxColumnTiles].posTile.y = countY * pixel * (float) tiles[i * maxColumnTiles].tileNumber;
    }


}

void ArenaMap::Tile::addTexturesToTiles() { //FIXME call this after fromMatrixToLayerMap
    int pixel = 32;

    tileSprite.setTexture(tileTexture);
    tileSprite.setTextureRect(sf::IntRect((int) posTile.x, (int) posTile.y, pixel, pixel));

}

