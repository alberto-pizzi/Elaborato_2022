//
// Created by Alberto Pizzi on 08/01/23.
//

#ifndef
ELABORATO_AI_H
#define
ELABORATO_AI_H

#include
"GameCharacter.h"


class AI {
private:
struct GraphTile{
float costF;
float costG;
float costH;
};

//TODO add graph with nodes
std::vector<GraphTile> graph; //tiles are nodes  (90x45)
std::vector<bool> mapWithObstacles;

std::vector<GraphTile> openList;
std::vector<GraphTile> closedList;

sf::Vector2i startingNode;
public:

explicit AI(const std::vector<bool>& mapWithObstacles);

void calculateWayWithAStar();

void updateStartingPoint(sf::Vector2i startingTile);



};


#endif //ELABORATO_AI_H
