//
// Created by alber on 03/11/2022.
//

#ifndef ELABORATO_ARENAMAP_H
#define ELABORATO_ARENAMAP_H

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

enum maps {
    desert = 0,
};

class ArenaMap {
private:
    std::ifstream readFile;
    TextureManager texmgr;

    class Tile {
    public:
        bool walkable;
        sf::Vector2f posTile;
        int tileNumber;
        int layer;
        sf::Texture tileTexture;
        sf::Sprite tileSprite;

        explicit Tile(int tile, int layerNumber, int map, TextureManager texManager);

        bool isWalkable(int tile, int layerNumber, int chosenMap);

        void addTexturesToTiles();
    };

protected:
    //TODO insert game view
    int maxRowTiles = tileMapDimensions(readFile, 'h');
    int maxColumnTiles = tileMapDimensions(readFile, 'w');
    std::unique_ptr<PosEntity> posEntity;
    std::vector<Tile> tiles; //matrix in the form of a vector
    //WARNING: update this array and enum for adding other maps
    std::string map[1] = {
            "res/maps/desertMap.xml"
    };
public:
    void createMap(int chosenMap);

    int layerStartVectorIndex(int layerNumber);

    int totalLayers(std::ifstream &file);

    void fromXMLtoTilesMatrix(std::ifstream &file, int maxJ, int maxI, int chosenMap);

    int tileMapDimensions(std::ifstream &file, char whichDim);

    void loadTextures(int chosenMap);

    void fromMatrixToLayerMap(int layerNumber);

    sf::Sprite drawMap(); //TODO implement it

};


#endif //ELABORATO_ARENAMAP_H
