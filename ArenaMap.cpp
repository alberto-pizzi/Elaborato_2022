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

ArenaMap::Tile::Tile(int tile, const std::string &nameMap, TextureManager texManager, int width, int height, int posX,
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
    if (loadMapFile(maxColumnTiles, maxRowTiles, chosenMap)) { //FIXME add exception for correct reading
        print3DVector();

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

bool ArenaMap::loadMapFile(int maxJ, int maxI, int chosenMap) {
    std::ifstream file;
    file.open(this->mapList[chosenMap]);
    if (!file) {
        return false;
    } else {
        std::string name;
        int tileNumber;

        /*
        ----WARNING: any file map must have this scheme and you must use ONLY one tileSheet per map----

        -Max tiles for column (in tiles)
        -Max tiles for row (in tiles)
        -Tile width size (in pixel)
        -Tile height size (in pixel)
        -Total layers
        -Total number of texture files (used by the map)
        -relative directory of file texture
        -width file (in pixel)
        -height file (in pixel)

         */

        //take tilemap data from file
        file >> this->nameMap >> this->maxColumnTiles >> this->maxRowTiles >> this->tileSizeX >> this->tileSizeY
             >> this->totalLayers >> this->nameFile >> this->widthFile >> this->heightFile;
        //load textures' Map
        texmgr.loadTexture(this->nameMap, this->nameFile);
        //start reading
        for (int countLayer = 0; countLayer < this->totalLayers; countLayer++) {
            std::vector<std::vector<Tile>> rows;
            for (int row = 0; row < this->maxRowTiles; row++) {
                std::vector<Tile> columns;
                for (int column = 0; column < this->maxColumnTiles; column++) {
                    file >> tileNumber;
                    columns.emplace_back(
                            Tile(tileNumber, this->nameMap, texmgr, this->widthFile, this->heightFile, row,
                                 column)); //TODO add progress bar (better with threads)
                }
                rows.emplace_back(columns);
            }
            tileMap.emplace_back(rows);
        }
        file.close();
        return true;
    }
}

void ArenaMap::print3DVector() {
    int count = 0;
    for (int l = 0; l < this->totalLayers; l++) {
        for (int i = 0; i < this->maxRowTiles; i++) {
            for (int j = 0; j < this->maxColumnTiles; j++) {
                std::cout << tileMap[l][i][j].tileNumber << " ";
                count++;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    std::cout << "TOTAL: " << tileMap.size() * tileMap[0].size() * tileMap[0][0].size() << std::endl;
}

void ArenaMap::drawMap(sf::RenderWindow &window) {
    for (int i = 0; i < this->maxRowTiles; i++) {
        for (int j = 0; j < this->maxColumnTiles; j++) {
            window.draw(this->tileMap[0][i][j].tileSprite);
            window.display();
        }
    }
}



