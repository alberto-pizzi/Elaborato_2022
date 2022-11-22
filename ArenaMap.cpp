//
// Created by alber on 03/11/2022.
//

#include "ArenaMap.h"

bool ArenaMap::Tile::isWalkable(int tile, int layerNumber, int chosenMap) {
    switch (chosenMap) {
        case desert:
            if ((layerNumber == 5) && (tile != 0)) //solid elements layer
                return false;
            else if ((layerNumber == 2) && (tile == 0)) //map limits
                return false;
            else if (((tile >= 41) && (tile <= 44)) || ((tile >= 201) && (tile <= 215)) ||
                     ((tile >= 241) && (tile <= 255)) || ((tile >= 281) && (tile <= 288)))
                return false;
            else
                return true;

            break;
    }
    return false;
}

ArenaMap::Tile::Tile(int tile, int widthTex, int posX, int posY, const sf::Texture &texture, int layer,
                     int tileSizeX, int tileSizeY, int chosenMap) : tileNumber(tile), layer(layer + 1), cellRow(posX),
                                                                    cellColumn(posY) {
    int tileTexturePosX, tileTexturePosY;
    this->walkable = isWalkable(tile, layer + 1, chosenMap);
    this->tileSprite.setTexture(texture);
    posTile = {static_cast<float>(posY * tileSizeX), static_cast<float>(posX * tileSizeY)};
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
        if ((l == 2) || (l == 3)) //3d layers
            continue;
        for (int i = 0; i < this->maxRowTiles; i++) {
            for (int j = 0; j < this->maxColumnTiles; j++) {
                window.draw(this->tileMap[l][i][j]->tileSprite);
            }
        }
    }
}

void ArenaMap::startingMap(sf::RenderWindow &window, std::unique_ptr<Mike> &mike) {
    this->playerView.reset(
            sf::FloatRect(static_cast<float>(0 * this->tileSizeX),
                          static_cast<float>(0 * this->tileSizeX), //FIXME 10x10
                          static_cast<float>(40 * this->tileSizeX), static_cast<float>(23 * this->tileSizeY)));
    window.setView(this->playerView);

    mike = std::unique_ptr<Mike>(new Mike());
}

void ArenaMap::loadTextures() {
    textureManager.loadTexture(this->nameMap, this->nameFile);
}

bool ArenaMap::isLegalMove(const sf::Vector2f &offset, GameCharacter &character) {
    bool isLegal[4] = {false, false, false, false};
    sf::Vector2f oldPos = character.getPos();
    sf::Vector2f newPos = oldPos + offset;
    sf::Vector2i actualTilePos = {static_cast<int>(oldPos.x / (float) tileSizeX),
                                  static_cast<int>(oldPos.y / (float) tileSizeY)};
    sf::Vector2i newTilePos = {static_cast<int>(newPos.x / (float) tileSizeX),
                               static_cast<int>(newPos.y / (float) tileSizeY)};

    //FIXME a lot of bugs
    if ((tileMap[4][actualTilePos.y][actualTilePos.x]->walkable) &&
        (newPos.x < tileMap[4][actualTilePos.y][actualTilePos.x]->posTile.x + static_cast<float>(tileSizeX)) &&
        (newPos.y < tileMap[4][actualTilePos.y][actualTilePos.x]->posTile.y + static_cast<float>(tileSizeY))) {
        return true;
    } else if ((tileMap[4][newTilePos.y][newTilePos.x]->walkable)) {
        return true;
    } else if ((!tileMap[4][newTilePos.y][newTilePos.x]->walkable)) {
        //left collision
        if (oldPos.x + static_cast<float>(tileSizeX) < tileMap[4][actualTilePos.y][actualTilePos.x]->posTile.x)
            isLegal[LEFT] = true;
        else if (offset.x <= 0)
            isLegal[LEFT] = true;
        //top collision
        if (oldPos.y + static_cast<float>(tileSizeY) < tileMap[4][actualTilePos.y][actualTilePos.x]->posTile.y)
            isLegal[TOP] = true;
        else if (offset.y <= 0)
            isLegal[TOP] = true;
        //right collision
        if (oldPos.x > tileMap[4][actualTilePos.y][actualTilePos.x]->posTile.x + static_cast<float>(tileSizeX))
            isLegal[RIGHT] = true;
        else if (offset.x >= 0)
            isLegal[RIGHT] = true;
        //bottom collision
        if (oldPos.y > tileMap[4][actualTilePos.y][actualTilePos.x]->posTile.y + static_cast<float>(tileSizeX))
            isLegal[BOTTOM] = true;
        else if (offset.y >= 0)
            isLegal[BOTTOM] = true;
    }

    if (isLegal[LEFT] || isLegal[TOP] || isLegal[RIGHT] || isLegal[BOTTOM])
        return true;
    else
        return false;

}

void ArenaMap::drawSolidLayers(sf::RenderWindow &window) {
    for (int l = 2; l <= 3; l++) {
        for (int i = 0; i < this->maxRowTiles; i++) {
            for (int j = 0; j < this->maxColumnTiles; j++) {
                window.draw(this->tileMap[l][i][j]->tileSprite);
            }
        }
    }
}



