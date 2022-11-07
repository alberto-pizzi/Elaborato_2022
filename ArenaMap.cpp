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

ArenaMap::Tile::Tile(int tile, int map, int layerNumber, TextureManager texManager, int width, int height, int posX,
                     int posY) { //FIXME check useless parameters

    int count = 0;
    bool found = false;
    this->tileNumber = tile;
    this->walkable = true;  //TODO remove it
    this->tileSprite.setTexture(texManager.getTextureRef("desert"));
    for (int i = 0; (i < height / 32) && (!found); i++) {
        for (int j = 0; (j < width / 32) && (!found); j++) {
            if (this->tileNumber == count) {
                this->tileSprite.setTextureRect(sf::IntRect(i * 32, j * 32, 32, 32));
                this->tileSprite.setPosition(sf::Vector2f((float) posX, (float) posY));
                found = true;
            }
            count++;
        }
    }

}

bool ArenaMap::loadMap(int chosenMap) {
    if (fromXMLtoTilesToMatrix(maxColumnTiles, maxRowTiles, chosenMap)) { //FIXME add exception for correct reading
        print3DVector(this->mapList[chosenMap].totLayers);

        return true;
    } else
        return false;
}

ArenaMap::~ArenaMap() {
}

ArenaMap::ArenaMap(int chosenMap) {
    if (!loadMap(chosenMap)) //FIXME add exception
        std::cerr << "Error during opening file" << std::endl;

}

bool ArenaMap::fromXMLtoTilesToMatrix(int maxJ, int maxI, int chosenMap) {
    int i = 0, openingLines = 6, closingLines = 4;
    int width = this->mapList[chosenMap].width;
    int height = this->mapList[chosenMap].height;
    std::ifstream file;
    file.open(this->mapList[chosenMap].nameFile);
    if (!file) {
        return false;
    } else {
        int totLayers = this->mapList[chosenMap].totLayers;
        bool beginFile = true;
        std::string line, number;
        //load textures' Map
        loadTextures(chosenMap);
        //skip initial XML lines
        if (beginFile) {
            for (int skipLines = 0; skipLines < openingLines; skipLines++)
                getline(file, line);
            beginFile = false;
        }
        //start reading
        for (int countLayer = 0; countLayer < totLayers; countLayer++) {
            std::vector<std::vector<Tile>> rows;
            while ((getline(file, line)) && (i < maxI)) {
                std::vector<Tile> colums;
                std::stringstream ss(line);
                for (int j = 0; j < maxJ; j++) {
                    getline(ss, number, ',');
                    colums.emplace_back(
                            Tile(std::stoi(number), chosenMap, countLayer + 1, texmgr, width, height, i,
                                 j)); //TODO add progress bar (better with threads)
                }
                i++;
                rows.emplace_back(colums);
            }
            layers.emplace_back(rows);
            i = 0;
            for (int skipLines = 0; skipLines < (closingLines - 1); skipLines++)
                getline(file, line);
        }
        file.close();
        return true;
    }
}

void ArenaMap::loadTextures(int chosenMap) {
    switch (chosenMap) {
        case desert:
            texmgr.loadTexture("desert", "res/textures/desertTiles32x32.png");
            break;
    }
}

void ArenaMap::print3DVector(int totLayers) {
    int count = 0;
    for (int l = 0; l < totLayers; l++) {
        for (int i = 0; i < maxRowTiles; i++) {
            for (int j = 0; j < maxColumnTiles; j++) {
                std::cout << layers[l][i][j].tileNumber << " ";
                count++;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    std::cout << "TOTAL: " << layers.size() * layers[0].size() * layers[0][0].size() << std::endl;
}

void ArenaMap::drawMap(sf::RenderWindow &window) {
    for (int i = 0; i < maxRowTiles; i++) {
        for (int j = 0; j < maxColumnTiles; j++) {
            window.draw(this->layers[1][i][j].tileSprite);
            window.display();
        }
    }
}



