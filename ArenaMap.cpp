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
        default:
            std::cerr << "ERROR: SELECTED MAP NOT EXIST" << std::endl;
            break;
    }
    return false;
}

ArenaMap::Tile::Tile(int tile, int widthTex, int posX, int posY, const sf::Texture &texture, int layer,
                     int tileSizeX, int tileSizeY, int chosenMap) : tileNumber(tile), layer(layer), cellRow(posX),
                                                                    cellColumn(posY) {
    int tileTexturePosX, tileTexturePosY;
    passable = isWalkable(tile, layer, chosenMap);
    tileSprite.setTexture(texture);
    posTile = {static_cast<float>(posY * tileSizeX), static_cast<float>(posX * tileSizeY)};
    tileTexturePosX = (tile % (widthTex / tileSizeX)) - 1;
    tileTexturePosY = tile / (widthTex / tileSizeY);
    if (tileTexturePosX < 0)
        tileTexturePosX = 0;
    if (tileTexturePosY < 0)
        tileTexturePosY = 0;
    tileSprite.setTextureRect(
            sf::IntRect(tileTexturePosX * tileSizeX, tileTexturePosY * tileSizeY, tileSizeX, tileSizeY));
    tileSprite.setPosition(
            sf::Vector2f(static_cast<float>(posY * tileSizeX), static_cast<float>(posX * tileSizeY)));
}

ArenaMap::~ArenaMap() = default;

ArenaMap::ArenaMap(int chosenMap, sf::RenderWindow &window, std::unique_ptr<Mike> &mike, const sf::Texture &mikeTexture,
                   const sf::Texture &weaponTexture, const sf::Texture &bulletTexture,
                   const TextureManager &guiTexManager,
                   float firstRoundStartingTime, sf::Vector2f viewSize) : viewSize(viewSize) {
    loadMapFile(chosenMap);
    startingMap(window, mike, mikeTexture, weaponTexture, bulletTexture, guiTexManager, firstRoundStartingTime);

    rowDice.setFaces(maxRowTiles - 2);
    columnDice.setFaces(maxColumnTiles - 2);
}

void ArenaMap::loadMapFile(int chosenMap) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(mapList[chosenMap]);
    }
    catch (std::ios_base::failure &e) {
        throw GameException("Error opening file map", mapList[chosenMap], false);
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
    file >> nameMap >> maxColumnTiles >> maxRowTiles >> tileSizeX >> tileSizeY
         >> totalLayers >> nameFile >> widthFile >> heightFile;
    //loadMapTextures textures' Map
    loadMapTextures();

    //start reading
    tileMap.reserve(totalLayers);
    for (int countLayer = 0; countLayer < totalLayers; countLayer++) {
        std::vector<std::vector<std::shared_ptr<Tile>>> rows;
        rows.reserve(maxRowTiles);
        for (int row = 0; row < maxRowTiles; row++) {
            std::vector<std::shared_ptr<Tile>> columns;
            columns.reserve(maxColumnTiles);
            for (int column = 0; column < maxColumnTiles; column++) {
                file >> nTile;
                columns.emplace_back(
                        new Tile(nTile, widthFile, row,
                                 column, mapTexturesManager.getTextureRef(nameMap),
                                 countLayer, tileSizeX, tileSizeY, chosenMap));
                if ((countLayer == solid_elements) && (nTile != 0) && isRealWall(chosenMap, nTile))
                    solidTiles.emplace_back(columns[column]);
                if ((!columns[column]->passable) &&
                    (((countLayer == solid_elements) || (countLayer == principal_floor))))
                    notPassableTiles.emplace_back(columns[column]);
            }
            rows.emplace_back(columns);
            }
            tileMap.emplace_back(rows);
        }
        file.close();
}

void ArenaMap::startingMap(sf::RenderWindow &window, std::unique_ptr<Mike> &mike, const sf::Texture &mikeTexture,
                           const sf::Texture &weaponTexture, const sf::Texture &bulletTexture,
                           const TextureManager &guiTexManager, float firstRoundStartingTime) {
    playerView.reset(
            sf::FloatRect(static_cast<float>(0 * tileSizeX),
                          static_cast<float>(0 * tileSizeX),
                          viewSize.x,
                          viewSize.y));

    //random spawned
    sf::Vector2i spawnTile = randomPassableTile();
    sf::Vector2f firstViewCenter;
    bool legalFirstCenter = false;

    mike = std::unique_ptr<Mike>(new Mike(mikeTexture, weaponTexture, bulletTexture, spawnTile, guiTexManager,
                                          {tileSizeX, tileSizeY},
                                          {GameCharacterSize::spriteSizeX, GameCharacterSize::spriteSizeY},
                                          firstRoundStartingTime));

    firstViewCenter = mike->getSpriteCenter();
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

    playerView.setCenter(legalViewCenter(mike->getSpriteCenter(), window.getSize(),
                                         {mike->getSprite().getGlobalBounds().width,
                                          mike->getSprite().getGlobalBounds().height}, firstViewCenter));
    window.setView(playerView);

    fillRectsVector();

    //create node map (for AI)
    createNodesMap();

}

void ArenaMap::loadMapTextures() {
    mapTexturesManager.loadTexture(nameMap, nameFile); //texture map

    //other  map tile sheet files...
}

bool ArenaMap::isMovingCorrectly(sf::Vector2f &offset, const GameCharacter &character) {
    sf::Vector2f oldPos = character.getSpriteCenter(); //centered position (from PosEntity)
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

    //left tile collides
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

        //right tile collides
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

    //top tile collides
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

        //bottom tile collides
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

sf::Vector2i ArenaMap::randomPassableTile() const {
    int tileSpawnX, tileSpawnY;

    //casual tile position. Spawn mike only when near tiles are passable.
    do {
        tileSpawnX = columnDice.roll(1) + 1;
        tileSpawnY = rowDice.roll(1) + 1;
    } while ((!tileMap[principal_floor][tileSpawnY][tileSpawnX]->passable) ||
             (!tileMap[principal_floor][tileSpawnY][tileSpawnX + 1]->passable) ||
             (!tileMap[principal_floor][tileSpawnY + 1][tileSpawnX]->passable) ||
             (!tileMap[principal_floor][tileSpawnY][tileSpawnX - 1]->passable) ||
             (!tileMap[principal_floor][tileSpawnY - 1][tileSpawnX]->passable) ||
             (!tileMap[design_elements][tileSpawnY][tileSpawnX]->passable) ||
             (!tileMap[design_elements][tileSpawnY][tileSpawnX + 1]->passable) ||
             (!tileMap[design_elements][tileSpawnY + 1][tileSpawnX]->passable) ||
             (!tileMap[design_elements][tileSpawnY][tileSpawnX - 1]->passable) ||
             (!tileMap[design_elements][tileSpawnY - 1][tileSpawnX]->passable) ||
             (!tileMap[solid_elements][tileSpawnY][tileSpawnX]->passable) ||
             (!tileMap[solid_elements][tileSpawnY][tileSpawnX + 1]->passable) ||
             (!tileMap[solid_elements][tileSpawnY + 1][tileSpawnX]->passable) ||
             (!tileMap[solid_elements][tileSpawnY][tileSpawnX - 1]->passable) ||
             (!tileMap[solid_elements][tileSpawnY - 1][tileSpawnX]->passable));

    return {tileSpawnX, tileSpawnY};
}

int ArenaMap::getTotalLayers() const {
    return totalLayers;
}

sf::Vector2f
ArenaMap::legalViewCenter(const sf::Vector2f &pos, const sf::Vector2u &windowSize, const sf::Vector2f &characterSize,
                          const sf::Vector2f &oldCenter) const {
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

int ArenaMap::weaponCutXSize(const GameCharacter &character) const {
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
        default:
            std::cerr << "ERROR: SELECTED MAP NOT EXIST" << std::endl;
            break;
    }
    return false;
}

void ArenaMap::drawLayer(sf::RenderWindow &window, int layer) const {
    for (int i = 0; i < maxRowTiles; i++) {
        for (int j = 0; j < maxColumnTiles; j++) {
            window.draw(tileMap[layer][i][j]->tileSprite);
        }
    }
}

bool ArenaMap::isWeaponOverTheWall(const GameCharacter &character) {
    sf::FloatRect delta;
    for (int i = 0; i < solidTiles.size(); i++) {
        if ((character.getSprite().getGlobalBounds().top >=
             solidTiles[i]->posTile.y + static_cast<float>(tileSizeY) - 5))
            if (character.weapon->hitBox.getGlobalBounds().intersects(solidTiles[i]->tileSprite.getGlobalBounds(),
                                                                      delta)) {
                if (delta.top + delta.height - 2 == solidTiles[i]->tileSprite.getGlobalBounds().top +
                                                    solidTiles[i]->tileSprite.getGlobalBounds().height - 2)
                    return true;
            }
    }
    return false;
}

bool ArenaMap::collidesWithSolidsOrBounds(sf::FloatRect bulletGlobalPos) const {
    //map limits
    if (bulletGlobalPos.left + bulletGlobalPos.width < 0 ||
        bulletGlobalPos.top + bulletGlobalPos.height < 0 ||
        bulletGlobalPos.left + bulletGlobalPos.width > static_cast<float>(maxColumnTiles * tileSizeX) ||
        bulletGlobalPos.top + bulletGlobalPos.height > static_cast<float>(maxRowTiles * tileSizeY))
        return true;
    else {
        //check if collides with solids
        sf::FloatRect delta;
        for (int i = 0; i < solidTiles.size(); i++)
            if ((bulletGlobalPos.intersects(solidTiles[i]->tileSprite.getGlobalBounds(), delta)) &&
                (std::max(delta.width, delta.height) >= static_cast<float>(tileSizeX) / 3))
                return true;
    }
    return false;
}

void ArenaMap::fillRectsVector() {
    sf::Vector2f beginPos = notPassableTiles[0]->posTile;
    sf::Vector2i previousTile = {notPassableTiles[0]->cellColumn, notPassableTiles[0]->cellRow};
    sf::Vector2i size = {tileSizeX, tileSizeY};
    bool end[2] = {false, false};

    for (int i = 1; i < notPassableTiles.size(); i++) {
        if ((notPassableTiles[i]->cellColumn == previousTile.x + 1) &&
            (notPassableTiles[i]->cellRow == previousTile.y)) {
            size.x += tileSizeX;
            previousTile.x = notPassableTiles[i]->cellColumn;
        } else if ((notPassableTiles[i]->cellColumn == previousTile.x) &&
                   (notPassableTiles[i]->cellRow == previousTile.y + 1)) {
            size.y += tileSizeY;
            previousTile.y = notPassableTiles[i]->cellRow;
        } else {
            sf::RectangleShape tmpRect;
            tmpRect.setSize({static_cast<float>(size.x), static_cast<float>(size.y)});
            tmpRect.setPosition(beginPos);
            tmpRect.setFillColor(sf::Color::Blue);
            rectWalls.emplace_back(tmpRect);

            beginPos = notPassableTiles[i]->posTile;
            size = {tileSizeX, tileSizeY};
            previousTile = {notPassableTiles[i]->cellColumn, notPassableTiles[i]->cellRow};
        }
        if (i == notPassableTiles.size() - 1) {
            sf::RectangleShape tmpRect;
            tmpRect.setSize({static_cast<float>(size.x), static_cast<float>(size.y)});
            tmpRect.setPosition(beginPos);
            tmpRect.setFillColor(sf::Color::Blue);
            rectWalls.emplace_back(tmpRect);
        }
    }
}

bool ArenaMap::collides(const sf::FloatRect &futureSpritePos) const {

    for (int i = 0; i < rectWalls.size(); i++) {
        if (futureSpritePos.intersects(rectWalls[i].getGlobalBounds()))
            return true;
    }
    return false;
}

bool
ArenaMap::collides(const sf::FloatRect &futureSpritePos, sf::RectangleShape &obstacle) const {

    for (int i = 0; i < rectWalls.size(); i++) {
        if (futureSpritePos.intersects(rectWalls[i].getGlobalBounds())) {
            obstacle = rectWalls[i];
            return true;
        }
    }
    return false;
}

void ArenaMap::createNodesMap() {
    for (int i = 0; i < maxRowTiles; i++) {
        std::vector<Node> column;
        for (int j = 0; j < maxColumnTiles; j++) {
            if ((!tileMap[principal_floor][i][j]->passable) || (!tileMap[solid_elements][i][j]->passable))
                column.emplace_back(j, i, false);
            else
                column.emplace_back(j, i, true);
        }
        nodeMap.emplace_back(column);
    }
}

int ArenaMap::getTileSizeX() const {
    return tileSizeX;
}

int ArenaMap::getTileSizeY() const {
    return tileSizeY;
}

sf::Vector2i ArenaMap::differentRandomPassableTileFromPreviousOne(sf::Vector2i previousTile) const {
    sf::Vector2i returnTile;

    do {
        returnTile = randomPassableTile();
    } while (returnTile == previousTile);

    return returnTile;
}





