//
// Created by alber on 03/11/2022.
//

#include "ArenaMap.h"

bool ArenaMap::Tile::isWalkable(int tile, int layerNumber, int chosenMap) const {
    //FIXME enum (magic numbers)
    switch (chosenMap) {
        case desert:
            if ((layerNumber == 5) && (tile != 0)) //solid elements layer
                return false;
            else if ((layerNumber == 2) && (tile == 0)) //map limits
                return false;
            else if (((tile >= 41) && (tile <= 48)) || ((tile >= 201) && (tile <= 215)) ||
                     ((tile >= 241) && (tile <= 255)) || ((tile >= 281) && (tile <= 295)) ||
                     ((tile >= 85) && (tile <= 88)))
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
//TODO deallocate memory
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
        //loadTextures textures' Map
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
                    if ((countLayer == 4) && (nTile != 0) && isRealWall(chosenMap, nTile))
                        solidTiles.emplace_back(columns[column]);

                }
                rows.emplace_back(columns);
            }
            tileMap.emplace_back(rows);
        }
        file.close();
}

void ArenaMap::drawFloorAndDesignElements(sf::RenderWindow &window) {
    for (int l = 0; l <= 2; l++) {
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
                          static_cast<float>(0 * this->tileSizeX),
                          static_cast<float>(this->tileView.x * this->tileSizeX),
                          static_cast<float>(this->tileView.y * this->tileSizeY)));

    //random spawn
    sf::Vector2i spawnTile = randomPassableTile();
    sf::Vector2f firstViewCenter;
    bool legalFirstCenter = false;


    mike = std::unique_ptr<Mike>(
            new Mike(textureManager.getTextureRef("mike"), textureManager.getTextureRef("handgun"), spawnTile,
                     {tileSizeX, tileSizeY},
                     {32, 32},
                     true));
    firstViewCenter = mike->getPos();
    sf::Vector2f distanceFromWindowCenter = {
            (static_cast<float>(window.getSize().x) / 2) +
            static_cast<float>(mike->getSprite().getTextureRect().width) / 2,
            (static_cast<float>(window.getSize().y) / 2) +
            static_cast<float>(mike->getSprite().getTextureRect().height) / 2};

    //check if view is inside the  map limits
    do {
        if (((firstViewCenter.x - distanceFromWindowCenter.x >= 0) &&
             (firstViewCenter.y - distanceFromWindowCenter.y >= 0)) &&
            ((firstViewCenter.x + distanceFromWindowCenter.x <=
              static_cast<float>(maxColumnTiles * tileSizeX)) &&
             (firstViewCenter.y + distanceFromWindowCenter.y <= static_cast<float>(maxRowTiles * tileSizeY))))

            legalFirstCenter = true;
        else {
            //check if view is inside map (horizontally)
            if ((firstViewCenter.x - distanceFromWindowCenter.x < 0) ||
                (firstViewCenter.x + distanceFromWindowCenter.x > static_cast<float>(maxColumnTiles * tileSizeX))) {
                if (firstViewCenter.x - distanceFromWindowCenter.x < 0)
                    firstViewCenter.x++;
                else if (firstViewCenter.x + distanceFromWindowCenter.x >
                         static_cast<float>(maxColumnTiles * tileSizeX))
                    firstViewCenter.x--;
            }
            //check if view is inside map (vertically)
            if ((firstViewCenter.y - distanceFromWindowCenter.y < 0) ||
                (firstViewCenter.y + distanceFromWindowCenter.y > static_cast<float>(maxRowTiles * tileSizeY))) {
                if (firstViewCenter.y - distanceFromWindowCenter.y < 0)
                    firstViewCenter.y++;
                else if (firstViewCenter.y + distanceFromWindowCenter.y >
                         static_cast<float>(maxColumnTiles * tileSizeX))
                    firstViewCenter.y--;

            }
        }
    } while (!legalFirstCenter);

    this->playerView.setCenter(legalViewCenter(mike->getPos(), window.getSize(),
                                               {mike->getSprite().getGlobalBounds().width,
                                                mike->getSprite().getGlobalBounds().height}, firstViewCenter));
    window.setView(this->playerView);

    findWallsCoordinates();
}

void ArenaMap::loadTextures() {
    textureManager.loadTexture(this->nameMap, this->nameFile); //texture map

    textureManager.loadTexture("mike", "res/textures/no_hands_mike.png");

    textureManager.loadTexture("handgun",
                               "res/textures/handgun_hand.png"); //spawning weapons (check that is equal in Playstate)

    textureManager.loadTexture("assaultRifle", "res/textures/assault_rifle.png"); //FIXME

    textureManager.loadTexture("shotgun", "res/textures/shotgun.png"); //FIXME

    //...
}

bool ArenaMap::isMovingCorrectly(sf::Vector2f &offset, const GameCharacter &character) {
    sf::Vector2f oldPos = character.getPos(); //centered position (from PosEntity)
    sf::Vector2i actualTilePos = {static_cast<int>(oldPos.x / (float) tileSizeX),
                                  static_cast<int>(oldPos.y / (float) tileSizeY)};
    int playerSideInTileContact[4] = {
            static_cast<int>(((character.getSprite().getGlobalBounds().left)) / (float) tileSizeX), //LEFT side
            static_cast<int>(
                    (character.getSprite().getGlobalBounds().left + character.getSprite().getGlobalBounds().width) /
                    (float) tileSizeX), //RIGHT side
            static_cast<int>(character.getSprite().getGlobalBounds().top / (float) tileSizeX), //UP side
            static_cast<int>(
                    (character.getSprite().getGlobalBounds().top + character.getSprite().getGlobalBounds().height) /
                    (float) tileSizeY), //DOWN side
    };
    sf::FloatRect tolerance;

    //left tile collision
    if ((offset.x > 0) && (((!tileMap[4][actualTilePos.y][playerSideInTileContact[RIGHT]]->passable) &&
                            (character.getSprite().getGlobalBounds().intersects(
                                    tileMap[4][actualTilePos.y][playerSideInTileContact[RIGHT]]->tileSprite.getGlobalBounds(),
                                    tolerance))) ||
                           ((!tileMap[1][actualTilePos.y][playerSideInTileContact[RIGHT]]->passable) &&
                            (character.getSprite().getGlobalBounds().intersects(
                                    tileMap[1][actualTilePos.y][playerSideInTileContact[RIGHT]]->tileSprite.getGlobalBounds(),
                                    tolerance)))) && (tolerance.width >= 0) && (tolerance.height >= 0)) {
        offset.x = 0;
    }

        //right tile collision
    else if ((offset.x < 0) && (((!tileMap[4][actualTilePos.y][playerSideInTileContact[LEFT]]->passable) &&
                                 (character.getSprite().getGlobalBounds().intersects(
                                         tileMap[4][actualTilePos.y][playerSideInTileContact[LEFT]]->tileSprite.getGlobalBounds(),
                                         tolerance))) ||
                                ((!tileMap[1][actualTilePos.y][playerSideInTileContact[LEFT]]->passable) &&
                                 (character.getSprite().getGlobalBounds().intersects(
                                         tileMap[1][actualTilePos.y][playerSideInTileContact[LEFT]]->tileSprite.getGlobalBounds(),
                                         tolerance)))) && (tolerance.width >= 0) && (tolerance.height >= 0)) {
        offset.x = 0;
    }

    //top tile collision
    if ((offset.y > 0) && (((!tileMap[4][playerSideInTileContact[DOWN]][actualTilePos.x]->passable) &&
                            (character.getSprite().getGlobalBounds().intersects(
                                    tileMap[4][playerSideInTileContact[DOWN]][actualTilePos.x]->tileSprite.getGlobalBounds(),
                                    tolerance))) ||
                           ((!tileMap[1][playerSideInTileContact[DOWN]][actualTilePos.x]->passable) &&
                            (character.getSprite().getGlobalBounds().intersects(
                                    tileMap[1][playerSideInTileContact[DOWN]][actualTilePos.x]->tileSprite.getGlobalBounds(),
                                    tolerance)))) && (tolerance.width >= 0) && (tolerance.height >= 0)) {
        offset.y = 0;
    }

        //bottom tile collision
    else if ((offset.y < 0) && (((!tileMap[4][playerSideInTileContact[UP]][actualTilePos.x]->passable) &&
                                 (character.getSprite().getGlobalBounds().intersects(
                                         tileMap[4][playerSideInTileContact[UP]][actualTilePos.x]->tileSprite.getGlobalBounds(),
                                         tolerance))) ||
                                ((!tileMap[1][playerSideInTileContact[UP]][actualTilePos.x]->passable) &&
                                 (character.getSprite().getGlobalBounds().intersects(
                                         tileMap[1][playerSideInTileContact[UP]][actualTilePos.x]->tileSprite.getGlobalBounds(),
                                         tolerance)))) && (tolerance.width >= 0) && (tolerance.height >= 0)) {
        offset.y = 0;
    }

    if ((offset.x == 0) && (offset.y == 0))
        return false;
    else
        return true;
}

void ArenaMap::drawSolidsAnd3DLayers(sf::RenderWindow &window) {
    for (int l = 3; l < this->totalLayers; l++) {
        for (int i = 0; i < this->maxRowTiles; i++) {
            for (int j = 0; j < this->maxColumnTiles; j++) {
                window.draw(this->tileMap[l][i][j]->tileSprite);
            }
        }
    }
}

sf::Vector2i ArenaMap::randomPassableTile() {
    srand(time(NULL));
    int tileSpawnX, tileSpawnY;

    //casual tile position
    do {
        tileSpawnX = (rand() % (this->maxColumnTiles - 1)) + 1;
        tileSpawnY = (rand() % (this->maxRowTiles - 1)) + 1;
    } while ((!tileMap[1][tileSpawnY][tileSpawnX]->passable) || (!tileMap[1][tileSpawnY][tileSpawnX + 1]->passable) ||
             (!tileMap[1][tileSpawnY + 1][tileSpawnX]->passable) ||
             (!tileMap[1][tileSpawnY][tileSpawnX - 1]->passable) ||
             (!tileMap[1][tileSpawnY - 1][tileSpawnX]->passable)); //spawn mike only when near tiles are passable

    return {tileSpawnX, tileSpawnY};
}

int ArenaMap::getTotalLayers() const {
    return totalLayers;
}

sf::Vector2f
ArenaMap::legalViewCenter(const sf::Vector2f &pos, const sf::Vector2u &windowSize, const sf::Vector2f &characterSize,
                          const sf::Vector2f &oldCenter) {
    sf::Vector2f distanceFromWindowCenter = {(static_cast<float>(windowSize.x) / 2) + (characterSize.x / 2),
                                             (static_cast<float>(windowSize.y) / 2) + (characterSize.y / 2)};
    sf::Vector2f newCenter = oldCenter;

    if (((pos.x - distanceFromWindowCenter.x >= 0) && (pos.y - distanceFromWindowCenter.y >= 0)) &&
        ((pos.x + distanceFromWindowCenter.x <=
          static_cast<float>(maxColumnTiles * tileSizeX)) &&
         (pos.y + distanceFromWindowCenter.y <= static_cast<float>(maxRowTiles * tileSizeY))))
        newCenter = pos;
    else if ((pos.x - distanceFromWindowCenter.x > 0) &&
             (pos.x + distanceFromWindowCenter.x < static_cast<float>(maxColumnTiles * tileSizeX)))
        newCenter = {pos.x, oldCenter.y};
    else if ((pos.y - distanceFromWindowCenter.y > 0) &&
             (pos.y + distanceFromWindowCenter.y < static_cast<float>(maxRowTiles * tileSizeY)))
        newCenter = {oldCenter.x, pos.y};
    return newCenter;
}

bool ArenaMap::isWeaponCuttable(const GameCharacter &character) {

    bool isInside = false;
    for (int i = 0; i < solidTiles.size(); i++) {
        if (((character.getSprite().getGlobalBounds().top + character.getSprite().getGlobalBounds().height) <=
             solidTiles[i]->posTile.y + static_cast<float>(tileSizeY)))
            if (character.weapon->hitBox.getGlobalBounds().intersects(solidTiles[i]->tileSprite.getGlobalBounds()))
                return true;
    }
    return false;
}

bool ArenaMap::isRealWall(int chosenMap, int nTile) {
    //these magic numbers are related to the tiles of texture map file
    switch (chosenMap) {
        case desert:
            for (int i = 0; i <= nTotRows; i++) {
                if ((nTile >= initialRealWall + (nTotColumns * i)) && (nTile <= endRealWall + (nTotColumns * i)))
                    return true;
            }
            return false;
            break;
    }
    return false;
}

void ArenaMap::findWallsCoordinates() {

    sf::Vector2f begin = solidTiles[0]->tileSprite.getPosition();
    sf::Vector2f end = {solidTiles[0]->tileSprite.getPosition().x + solidTiles[0]->tileSprite.getGlobalBounds().width,
                        solidTiles[0]->tileSprite.getPosition().y + solidTiles[0]->tileSprite.getGlobalBounds().height};
    sf::Vector2i tmpTile = {solidTiles[0]->cellColumn, solidTiles[0]->cellRow};

    for (int i = 1; i < solidTiles.size(); i++) {
        if ((solidTiles[i]->cellColumn == tmpTile.x + 1) && (solidTiles[i]->cellRow == tmpTile.y)) {
            end = {solidTiles[i]->tileSprite.getPosition().x + solidTiles[i]->tileSprite.getGlobalBounds().width,
                   solidTiles[i]->tileSprite.getPosition().y + solidTiles[i]->tileSprite.getGlobalBounds().height};
            tmpTile.x = solidTiles[i]->cellColumn;
        } else {
            walls.push_back({begin, end});
            begin = solidTiles[i]->tileSprite.getPosition();
            tmpTile = {solidTiles[i]->cellColumn, solidTiles[i]->cellRow};
        }
        if (i == solidTiles.size() - 1) {
            end = {solidTiles[i]->tileSprite.getPosition().x + solidTiles[i]->tileSprite.getGlobalBounds().width,
                   solidTiles[i]->tileSprite.getPosition().y + solidTiles[i]->tileSprite.getGlobalBounds().height};
            walls.push_back({begin, end});
        }
    }
}





