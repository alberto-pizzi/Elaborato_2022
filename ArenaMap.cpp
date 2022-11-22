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
    this->passable = isWalkable(tile, layer + 1, chosenMap);
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

    mike = std::unique_ptr<Mike>(new Mike());

    this->playerView.setCenter(mike->getPos());
    window.setView(this->playerView);
}

void ArenaMap::loadTextures() {
    textureManager.loadTexture(this->nameMap, this->nameFile);
}

bool ArenaMap::isLegalMove(sf::Vector2f &offset, const GameCharacter &character, const bool direction[]) {
    bool isLegal[4] = {false, false, false, false};
    sf::Vector2f oldPos = character.getPos();
    sf::Vector2f newPos = oldPos + offset;
    sf::Vector2i actualTilePos = {static_cast<int>(oldPos.x / (float) tileSizeX),
                                  static_cast<int>(oldPos.y / (float) tileSizeY)};
    sf::Vector2i newTilePos = {static_cast<int>(newPos.x / (float) tileSizeX),
                               static_cast<int>(newPos.y / (float) tileSizeY)};
    sf::Vector2f characterCenter = {character.getPos().x - static_cast<float>(tileSizeX) / 2,
                                    character.getPos().y - static_cast<float>(tileSizeY) / 2};

    //left tile collision
    if ((!tileMap[4][newTilePos.y][static_cast<int>((characterCenter.x + 5) / (float) tileSizeX)]->passable)) {
        if (character.getCharacter().getGlobalBounds().intersects(
                tileMap[4][newTilePos.y][static_cast<int>((characterCenter.x + (float) tileSizeX - 1) /
                                                          (float) tileSizeX)]->tileSprite.getGlobalBounds()))
            if (offset.x > 0)
                offset.x = 0;
    }
        //right tile collision
    else if (!tileMap[4][newTilePos.y][newTilePos.x]->passable) {
        if (offset.x < 0)
            offset.x = 0;
    }
    //top tile collision
    if (!tileMap[4][static_cast<int>((oldPos.y - 16 + (float) tileSizeY) /
                                     (float) tileSizeY)][newTilePos.x]->passable) {
        if (offset.y > 0)
            offset.y = 0;
    }

        //bottom tile collision
    else if (!tileMap[4][newTilePos.y][newTilePos.x]->passable) {
        if (offset.y < 0)
            offset.y = 0;
    }

    if ((offset.x == 0) && (offset.y == 0))
        return false;
    else
        return true;


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



