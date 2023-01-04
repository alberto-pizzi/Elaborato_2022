//
// Created by alber on 03/11/2022.
//

#ifndef ELABORATO_ARENAMAP_H
#define ELABORATO_ARENAMAP_H

#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "PosEntity.h"
#include "TextureManager.h"
#include "GameException.h"
#include "Mike.h"
#include "GameCharacter.h"
#include "Dice.h"

enum mapNumber {
    desert = 0,
};
enum Layers {
    background = 0, principal_floor, design_elements, layer_3d, solid_elements, last_layer,
};

class ArenaMap {
private:
    enum nTileFromFile {
        initialRealWall = 20, endRealWall = 38, nTotRows = 8, nTotColumns = 40,
    };
    enum Collisions {
        LEFT = 0,
        RIGHT = 1,
        UP = 2,
        DOWN = 3,
    };

    class Tile {
    public:
        bool passable;
        sf::Vector2f posTile;
        int tileNumber;
        int layer;
        int cellColumn;
        int cellRow;
        sf::Sprite tileSprite;

        Tile(int tile, int widthTex, int posX, int posY, const sf::Texture &texture, int layer,
             int tileSizeX, int tileSizeY, int chosenMap);

        bool isWalkable(int tile, int layerNumber, int chosenMap) const;
    };

    Dice rowDice;
    Dice columnDice;
protected:
    struct Walls {
        sf::Vector2f begin;
        sf::Vector2f end;
    };
    int maxColumnTiles;
    int maxRowTiles;
    int tileSizeX;
    int tileSizeY;
    int totalLayers;
    int widthFile;
    int heightFile;
    std::string nameFile;
    std::string nameMap;
    std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> tileMap;
    std::vector<std::shared_ptr<Tile>> solidTiles;
    std::vector<std::shared_ptr<Tile>> notPassableTiles;
    std::vector<Walls> walls;
    //WARNING: updateNotCyclicalAnimation this string array and enum for adding other Map
    std::string mapList[1] = {
            "res/maps/desertMap.txt",
    };
    std::unique_ptr<PosEntity> entity;
    sf::Vector2i tileView = {40, 23};
public:
    std::vector<sf::RectangleShape> rectWalls;

    TextureManager mapTexturesManager;
    sf::View playerView;

    explicit ArenaMap(int chosenMap, sf::RenderWindow &window, std::unique_ptr<Mike> &mike,
                      const sf::Texture &mikeTexture,
                      const sf::Texture &weaponTexture, const sf::Texture &bulletTexture,
                      const TextureManager &guiTexManager,
                      float firstRoundStartingTime);

    virtual ~ArenaMap();

    int getTotalLayers() const;

    void loadMapFile(int chosenMap);

    void startingMap(sf::RenderWindow &window, std::unique_ptr<Mike> &mike, const sf::Texture &mikeTexture,
                     const sf::Texture &weaponTexture, const sf::Texture &bulletTexture,
                     const TextureManager &guiTexManager, float firstRoundStartingTime);

    void loadMapTextures();

    void drawLayer(sf::RenderWindow &window, int layer) const;

    bool
    isMovingCorrectly(sf::Vector2f &offset, const GameCharacter &character);

    sf::Vector2i randomPassableTile() const;

    sf::Vector2f
    legalViewCenter(const sf::Vector2f &pos, const sf::Vector2u &windowSize, const sf::Vector2f &characterSize,
                    const sf::Vector2f &oldCenter) const;

    int weaponCutXSize(const GameCharacter &character) const;

    bool isWeaponOverTheWall(const GameCharacter &character);

    bool isRealWall(int chosenMap, int nTile);

    void findWallsCoordinates(); //TODO check if it is useful

    bool collidesWithSolidsOrBounds(sf::FloatRect bulletGlobalPos) const;

    void fillRectsVector();

    bool collides(const sf::FloatRect &futureSpritePos) const;

    void autonomousMovementDecisions(sf::Vector2f &offset);

};


#endif //ELABORATO_ARENAMAP_H
