//
// Created by Alberto Pizzi on 08/01/23.
//

#include "AI.h"

AI::AI(const std::vector<std::vector<Node>> &map) {
    this->map = map;
}

std::vector<Node> AI::findPath(sf::Vector2i startTile, sf::Vector2i targetTile) {
    //init lists
    openList.clear();
    openList.clear();

    //add starting node into open list
    std::shared_ptr<Node> startNode = std::make_shared<Node>(startTile.x, startTile.y, true);
    startNode->gCost = 0;
    startNode->hCost = manhattanDistance(startTile, targetTile);
    startNode->fCost = startNode->gCost + startNode->hCost;
    openList.push_back(startNode);

    //init current node with the starting node
    std::shared_ptr<Node> currentNode = startNode;

    while (!openList.empty()) {

    }

    return {};


}

int AI::manhattanDistance(sf::Vector2i startTile, sf::Vector2i targetTile) const {
    return std::abs(targetTile.x - startTile.x) + std::abs(targetTile.y - startTile.y);
}

