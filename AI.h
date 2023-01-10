//
// Created by Alberto Pizzi on 08/01/23.
//

#ifndef ELABORATO_AI_H
#define ELABORATO_AI_H

#include "GameCharacter.h"
#include "Node.h"

class AI {
private:
    std::vector<std::vector<Node>> map; //nodes map  (90x45)

    std::vector<std::shared_ptr<Node>> openList;
    std::vector<std::shared_ptr<Node>> closedList;


public:

    explicit AI(const std::vector<std::vector<Node>> &map);

    std::vector<Node> findPath(sf::Vector2i startTile, sf::Vector2i targetTile);

    int calculateManhattanDistance(sf::Vector2i startTile, sf::Vector2i targetTile) const;

    std::vector<Node> reconstructPath(const std::shared_ptr<Node> &startNode, std::shared_ptr<Node> &currentNode);

    bool isInsideClosedList(const std::shared_ptr<Node> &currentNode);

    bool isInsideOpenList(const std::shared_ptr<Node> &currentNode);

    int calculateGCost(sf::Vector2i start, sf::Vector2i end) const;


};


#endif //ELABORATO_AI_H
