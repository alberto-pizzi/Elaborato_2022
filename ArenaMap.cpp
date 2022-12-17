//
// Created by alber on 03/11/2022.
//

#include "ArenaMap.h"

bool ArenaMap::Tile::isWalkable(int tile, int layerNumber, int chosenMap) const {
    switch (chosenMap) {
        case desert:
            enum desertTileNumbers {
                beginMapLittleLimits = 41,
                endMapLittleLimits = 48,
                beginRockSideLimits = 201,
                endRockSideLimits = 215,
                beginRockSideLimits2 = 241,
                endRockSideLimits2 = 255,
                beginRockSideLimits3 = 281,
                endRockSideLimits3 = 295,
                beginRockDiagonalLimits = 85,
                endRockDiagonalLimits = 88,

                multiplierFactorRow = 40,
                //tree
                beginTreeRoots1 = 954,
                endTreeRoots1 = 956,
                beginTreeRoots2 = 994,
                endTreeRoots2 = 996,

                //wheels
                beginWheel1 = 668,
                endWheel1 = 669,
                beginWheel2 = 708,
                endWheel2 = 709,

                //cellar
                beginCellar1 = 588,
                endCellar1 = 589,
                beginCellar2 = 628,
                endCellar2 = 629,

                //bonfire
                beginBonfire1 = 665,
                endBonfire1 = 666,
                beginBonfire2 = 705,
                endBonfire2 = 706,

                //barrel
                endBarrel = 667,

                //char and shelf
                beginShelf = 623,
                endShelf = 624,
                chair = 701,

            };

            if ((layerNumber == solid_elements) && (tile != 0)) //solid elements layer
                return false;
            else if ((layerNumber == principal_floor) && (tile == 0)) //map limits
                return false;
            else if (((tile >= beginMapLittleLimits) && (tile <= endMapLittleLimits)) ||
                     ((tile >= beginRockSideLimits) && (tile <= endRockSideLimits)) ||
                     ((tile >= beginRockSideLimits2) && (tile <= endRockSideLimits2)) ||
                     ((tile >= beginRockSideLimits3) && (tile <= endRockSideLimits3)) ||
                     ((tile >= beginRockDiagonalLimits) && (tile <= endRockDiagonalLimits)))
                return false;
            else if (
                    ((tile >= beginWheel1) && (tile <= endWheel1)) ||
                    ((tile >= beginWheel2) && (tile <= beginWheel2)) ||
                    ((tile >= beginCellar1) && (tile <= endCellar1)) ||
                    ((tile >= beginCellar2) && (tile <= endCellar2)) ||
                    ((tile >= beginBonfire1) && (tile <= endBonfire1)) ||
                    ((tile >= beginBonfire2) && (tile <= endBonfire2)) ||
                    ((tile >= beginShelf) && (tile <= endShelf)) ||
                    ((tile == endBarrel) || (tile == chair)))
                return false;
            else
                return true;

            break;
    }
    return false;
}

ArenaMap::Tile::Tile(int tile, int widthTex, int posX, int posY, const sf::Texture &texture, int layer,
                     int tileSizeX, int tileSizeY, int chosenMap) : tileNumber(tile), layer(layer), cellRow(posX),
                                                                    cellColumn(posY) {
    int tileTexturePosX, tileTexturePosY;
    this->passable = isWalkable(tile, layer, chosenMap);
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
                    if ((countLayer == solid_elements) && (nTile != 0) && isRealWall(chosenMap, nTile))
                        solidTiles.emplace_back(columns[column]);

                }
                rows.emplace_back(columns);
            }
            tileMap.emplace_back(rows);
        }
        file.close();
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
    if ((offset.x > 0) && ((((!tileMap[solid_elements][actualTilePos.y][playerSideInTileContact[RIGHT]]->passable) ||
                             (!tileMap[design_elements][actualTilePos.y][playerSideInTileContact[RIGHT]]->passable)) &&
                            (character.getSprite().getGlobalBounds().intersects(
                                    tileMap[solid_elements][actualTilePos.y][playerSideInTileContact[RIGHT]]->tileSprite.getGlobalBounds(),
                                    tolerance))) ||
                           ((!tileMap[principal_floor][actualTilePos.y][playerSideInTileContact[RIGHT]]->passable) &&
                            (character.getSprite().getGlobalBounds().intersects(
                                    tileMap[principal_floor][actualTilePos.y][playerSideInTileContact[RIGHT]]->tileSprite.getGlobalBounds(),
                                    tolerance)))) && (tolerance.width >= 0) && (tolerance.height >= 0)) {
        offset.x = 0;
    }

        //right tile collision
    else if ((offset.x < 0) &&
             ((((!tileMap[solid_elements][actualTilePos.y][playerSideInTileContact[LEFT]]->passable) ||
                (!tileMap[design_elements][actualTilePos.y][playerSideInTileContact[LEFT]]->passable)) &&
               (character.getSprite().getGlobalBounds().intersects(
                       tileMap[solid_elements][actualTilePos.y][playerSideInTileContact[LEFT]]->tileSprite.getGlobalBounds(),
                       tolerance))) ||
              ((!tileMap[principal_floor][actualTilePos.y][playerSideInTileContact[LEFT]]->passable) &&
               (character.getSprite().getGlobalBounds().intersects(
                       tileMap[principal_floor][actualTilePos.y][playerSideInTileContact[LEFT]]->tileSprite.getGlobalBounds(),
                       tolerance)))) && (tolerance.width >= 0) && (tolerance.height >= 0)) {
        offset.x = 0;
    }

    //top tile collision
    if ((offset.y > 0) && ((((!tileMap[solid_elements][playerSideInTileContact[DOWN]][actualTilePos.x]->passable) ||
                             (!tileMap[design_elements][playerSideInTileContact[DOWN]][actualTilePos.x]->passable)) &&
                            (character.getSprite().getGlobalBounds().intersects(
                                    tileMap[solid_elements][playerSideInTileContact[DOWN]][actualTilePos.x]->tileSprite.getGlobalBounds(),
                                    tolerance))) ||
                           ((!tileMap[principal_floor][playerSideInTileContact[DOWN]][actualTilePos.x]->passable) &&
                            (character.getSprite().getGlobalBounds().intersects(
                                    tileMap[principal_floor][playerSideInTileContact[DOWN]][actualTilePos.x]->tileSprite.getGlobalBounds(),
                                    tolerance)))) && (tolerance.width >= 0) && (tolerance.height >= 0)) {
        offset.y = 0;
    }

        //bottom tile collision
    else if ((offset.y < 0) && ((((!tileMap[solid_elements][playerSideInTileContact[UP]][actualTilePos.x]->passable) ||
                                  (!tileMap[design_elements][playerSideInTileContact[UP]][actualTilePos.x]->passable)) &&
                                 (character.getSprite().getGlobalBounds().intersects(
                                         tileMap[solid_elements][playerSideInTileContact[UP]][actualTilePos.x]->tileSprite.getGlobalBounds(),
                                         tolerance))) ||
                                ((!tileMap[principal_floor][playerSideInTileContact[UP]][actualTilePos.x]->passable) &&
                                 (character.getSprite().getGlobalBounds().intersects(
                                         tileMap[principal_floor][playerSideInTileContact[UP]][actualTilePos.x]->tileSprite.getGlobalBounds(),
                                         tolerance)))) && (tolerance.width >= 0) && (tolerance.height >= 0)) {
        offset.y = 0;
    }

    if ((offset.x == 0) && (offset.y == 0))
        return false;
    else
        return true;
}

sf::Vector2i ArenaMap::randomPassableTile() {
    srand(time(NULL));
    int tileSpawnX, tileSpawnY;

    //casual tile position
    do {
        tileSpawnX = (rand() % (this->maxColumnTiles - 1)) + 1;
        tileSpawnY = (rand() % (this->maxRowTiles - 1)) + 1;
    } while ((!tileMap[principal_floor][tileSpawnY][tileSpawnX]->passable) ||
             (!tileMap[1][tileSpawnY][tileSpawnX + 1]->passable) ||
             (!tileMap[principal_floor][tileSpawnY + 1][tileSpawnX]->passable) ||
             (!tileMap[principal_floor][tileSpawnY][tileSpawnX - 1]->passable) ||
             (!tileMap[principal_floor][tileSpawnY -
                                        1][tileSpawnX]->passable)); //spawn mike only when near tiles are passable

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

int ArenaMap::weaponCutXSize(const GameCharacter &character) {
    sf::FloatRect delta;
    for (int i = 0; i < solidTiles.size(); i++) {
        //if (((character.weapon->getDegrees() >= 35) && (character.weapon->weaponSprite.getScale().x == 1)) || (character.weapon->getDegrees() <= -35) && (character.weapon->weaponSprite.getScale().x == -1))
        if (((character.getSprite().getGlobalBounds().top + character.getSprite().getGlobalBounds().height) <=
             solidTiles[i]->posTile.y + static_cast<float>(tileSizeY)))
            if (character.weapon->hitBox.getGlobalBounds().intersects(solidTiles[i]->tileSprite.getGlobalBounds(),
                                                                      delta)) {
                if (delta.top + delta.height - 2 == solidTiles[i]->tileSprite.getGlobalBounds().top +
                                                    solidTiles[i]->tileSprite.getGlobalBounds().height - 2)
                    return character.weapon->hitBox.getSize().x + std::abs(
                            character.weapon->hitBox.getGlobalBounds().left -
                            character.weapon->weaponSprite.getGlobalBounds().left) -
                           std::max(delta.width, delta.height) - 2;
            }
    }
    return 0;
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

void ArenaMap::drawLayer(sf::RenderWindow &window, int layer) {
    for (int i = 0; i < this->maxRowTiles; i++) {
        for (int j = 0; j < this->maxColumnTiles; j++) {
            window.draw(this->tileMap[layer][i][j]->tileSprite);
        }
    }
}

bool ArenaMap::isWeaponOverTheWall(const GameCharacter &character) {
    sf::FloatRect delta;
    for (int i = 0; i < solidTiles.size(); i++) {
        //if (((character.weapon->getDegrees() >= 35) && (character.weapon->weaponSprite.getScale().x == 1)) || (character.weapon->getDegrees() <= -35) && (character.weapon->weaponSprite.getScale().x == -1))
        if ((character.getSprite().getGlobalBounds().top >=
             solidTiles[i]->posTile.y + static_cast<float>(tileSizeY) - 5))
            if (character.weapon->hitBox.getGlobalBounds().intersects(solidTiles[i]->tileSprite.getGlobalBounds(),
                                                                      delta)) {
                //std::cout<<"Left: "<<delta.left<<" Top: "<<delta.top<<" Width: "<<delta.width<<" Height: "<<delta.height<<std::endl;
                if (delta.top + delta.height - 2 == solidTiles[i]->tileSprite.getGlobalBounds().top +
                                                    solidTiles[i]->tileSprite.getGlobalBounds().height - 2)
                    return true;
            }
    }
    return false;
}





