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

enum mapNumber {
    desert = 0,
};

class ArenaMap {
private:


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

protected:
    int maxColumnTiles;
    int maxRowTiles;
    int tileSizeX;
    int tileSizeY;
    int totalLayers;
    int widthFile;
    int heightFile;
    std::string nameFile;
    std::string nameMap;
    std::vector<std::vector<std::vector<Tile *>>> tileMap;
    //WARNING: update this string array and enum for adding other Map
    std::string mapList[1] = {
            "res/maps/desertMap.txt",
    };
    std::unique_ptr<PosEntity> entity;
    sf::Vector2i tileView = {40, 23};
public:
    TextureManager textureManager;
    sf::View playerView;

    explicit ArenaMap(int chosenMap, sf::RenderWindow &window, std::unique_ptr<Mike> &mike);

    virtual ~ArenaMap();

    int getTotalLayers() const;

    void loadMap(int chosenMap, sf::RenderWindow &window, std::unique_ptr<Mike> &mike);

    void loadMapFile(int chosenMap);

    void startingMap(sf::RenderWindow &window, std::unique_ptr<Mike> &mike);

    void loadTextures();

    void drawFloorAndDesignElements(sf::RenderWindow &window);

    void drawSolidsAnd3DLayers(sf::RenderWindow &window);

    bool
    isMovingCorrectly(sf::Vector2f &offset, const GameCharacter &character);

    sf::Vector2i randomPassableTile();

    sf::Vector2f
    legalViewCenter(const sf::Vector2f &pos, const sf::Vector2u &windowSize, const sf::Vector2f &characterSize,
                    const sf::Vector2f &oldCenter);
};


#endif //ELABORATO_ARENAMAP_H
