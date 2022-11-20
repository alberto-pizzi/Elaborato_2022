//
// Created by alber on 03/11/2022.
//

#include "ArenaMap.h"

bool ArenaMap::Tile::isWalkable(int tile, int layerNumber, int chosenMap) {
    switch (chosenMap) {
        case desert:
            if ((layerNumber == 5) && (tile != 0)) //solid elements layer
                return false;
            else
                return true;

            break;
    }
    return false;
}

ArenaMap::Tile::Tile(int tile, int widthTex, int posX, int posY, const sf::Texture &texture, int layer,
                     int tileSizeX, int tileSizeY, int chosenMap) : tileNumber(tile), layer(layer + 1) {
    int tileTexturePosX, tileTexturePosY;
    this->walkable = isWalkable(tile, layer + 1, chosenMap);
    this->tileSprite.setTexture(texture);
    tileTexturePosX = (tile % (widthTex / tileSizeX)) - 1;
    tileTexturePosY = tile / (widthTex / tileSizeY);
    if (tileTexturePosX < 0)
        tileTexturePosX = 0;
    if (tileTexturePosY < 0)
        tileTexturePosY = 0;
    this->tileSprite.setTextureRect(
            sf::IntRect(tileTexturePosX * tileSizeX, tileTexturePosY * tileSizeY, tileSizeX, tileSizeY));
    this->tileSprite.setPosition(
            sf::Vector2f(static_cast<float>(posY * tileSizeX), static_cast<float>(posX * tileSizeY)));
}

void ArenaMap::loadMap(int chosenMap, sf::RenderWindow &window, std::unique_ptr<Mike> &mike) {
    loadMapFile(chosenMap);
    startingMap(window, mike);
}

ArenaMap::~ArenaMap() {
}

ArenaMap::ArenaMap(int chosenMap, sf::RenderWindow &window, std::unique_ptr<Mike> &mike) {
    loadMap(chosenMap, window, mike);
}

void ArenaMap::loadMapFile(int chosenMap) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(this->mapList[chosenMap]);
    }
    catch (std::ios_base::failure &e) {
        throw GameException("Error opening file map", this->mapList[chosenMap], false);
    }
    std::string name;
    int nTile;
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
        loadTextures();

        //start reading
        tileMap.reserve(this->totalLayers);
        for (int countLayer = 0; countLayer < this->totalLayers; countLayer++) {
            std::vector<std::vector<Tile *>> rows;
            rows.reserve(this->maxRowTiles);
            for (int row = 0; row < this->maxRowTiles; row++) {
                std::vector<Tile *> columns;
                columns.reserve(this->maxColumnTiles);
                for (int column = 0; column < this->maxColumnTiles; column++) {
                    file >> nTile;
                    columns.emplace_back(
                            new Tile(nTile, this->widthFile, row,
                                     column, this->textureManager.getTextureRef(this->nameMap),
                                     countLayer, this->tileSizeX, this->tileSizeY, chosenMap));

                }
                rows.emplace_back(columns);
            }
            tileMap.emplace_back(rows);
        }
        file.close();
}

void ArenaMap::drawMap(sf::RenderWindow &window) {
    for (int l = 0; l < this->totalLayers; l++) {
        for (int i = 0; i < this->maxRowTiles; i++) {
            for (int j = 0; j < this->maxColumnTiles; j++) {
                window.draw(this->tileMap[l][i][j]->tileSprite);
            }
        }
    }
}

void ArenaMap::startingMap(sf::RenderWindow &window, std::unique_ptr<Mike> &mike) {
    this->playerView.reset(
            sf::FloatRect(static_cast<float>(10 * this->tileSizeX), static_cast<float>(10 * this->tileSizeX),
                          static_cast<float>(30 * this->tileSizeX), static_cast<float>(20 * this->tileSizeY)));
    window.setView(this->playerView);

    //TODO insert mike spawner
    mike = std::unique_ptr<Mike>(new Mike());


}

void ArenaMap::loadTextures() {
    textureManager.loadTexture(this->nameMap, this->nameFile);
}



