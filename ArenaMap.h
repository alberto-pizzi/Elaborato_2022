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
    TextureManager textureManager;

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

        bool isWalkable(int tile, int layerNumber, int chosenMap); //FIXME improve it (optimization)
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
    //WARNING: update this struct array and enum for adding other Map
    std::string mapList[1] = {
            "res/maps/desertMap.txt",
    };
    std::unique_ptr<PosEntity> entity;
public:
    sf::View playerView;

    explicit ArenaMap(int chosenMap, sf::RenderWindow &window, std::unique_ptr<Mike> &mike);

    virtual ~ArenaMap();

    void loadMap(int chosenMap, sf::RenderWindow &window, std::unique_ptr<Mike> &mike);

    void loadMapFile(int chosenMap);

    void startingMap(sf::RenderWindow &window, std::unique_ptr<Mike> &mike); //TODO finish and implement it

    void loadTextures();

    void drawMap(sf::RenderWindow &window);

    void drawSolidLayers(sf::RenderWindow &window);

    bool isLegalMove(sf::Vector2f &offset, const GameCharacter &character, const bool direction[]); //FIXME it has bug
};


#endif //ELABORATO_ARENAMAP_H
