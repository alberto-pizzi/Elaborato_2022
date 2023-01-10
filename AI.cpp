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
    startNode->hCost = calculateManhattanDistance(startTile, targetTile);
    startNode->fCost = startNode->gCost + startNode->hCost;
    openList.push_back(startNode);

    //init current node with the starting node
    std::shared_ptr<Node> currentNode = startNode;
    currentNode->setAdjacentNodes(map, startNode);

    //add neighbours node into open list
    openList.push_back(currentNode);



    // loop until path is found or no more nodes to evaluate
    while (!openList.empty()) {

        // find node with lowest fCost in openList
        std::shared_ptr<Node> lowestFCostNode = openList[0];
        int currentIndex = 0;
        for (int i = 1; i < openList.size(); ++i) {
            if (openList[i]->fCost < currentNode->fCost) {
                currentNode = openList[i];
                currentIndex = i;
            }
        }

        if (currentNode->tile == targetTile)
            return reconstructPath(startNode, currentNode); //FIXME


        openList.erase(openList.begin() + currentIndex);
        closedList.push_back(currentNode);

        //FIXME check code after this line

        currentNode->setAdjacentNodes(map, currentNode);
        for (int j = 0; j < currentNode->adjacentNodes.size(); j++) {

            if (isInsideClosedList(currentNode))
                continue;

            if (!isInsideOpenList(currentNode))
                openList.push_back(currentNode);

        }


    }


}

int AI::calculateManhattanDistance(sf::Vector2i startTile, sf::Vector2i targetTile) const {
    return std::abs(targetTile.x - startTile.x) + std::abs(targetTile.y - startTile.y);
}

std::vector<Node>
AI::reconstructPath(const std::shared_ptr<Node> &startNode, std::shared_ptr<Node> &currentNode) {

    std::vector<Node> path;
    path.emplace_back(*currentNode);

    while (currentNode->parent != nullptr) {
        currentNode = currentNode->parent;
        path.emplace_back(*currentNode);
    }

    return path;
}

bool AI::isInsideClosedList(const std::shared_ptr<Node> &currentNode) {
    bool isItInTheClosedList = false;
    for (int i = 0; i < closedList.size(); i++) {
        if (currentNode == closedList[i]) {
            isItInTheClosedList = true;
            break;
        }
    }
    return isItInTheClosedList;
}

bool AI::isInsideOpenList(const std::shared_ptr<Node> &currentNode) {
    bool isItInTheOpenList = false;
    for (int i = 0; i < openList.size(); i++) {
        if (currentNode == openList[i]) {
            isItInTheOpenList = true;
            break;
        }
    }
    return isItInTheOpenList;
}

int AI::calculateGCost(sf::Vector2i start, sf::Vector2i end) const {
    int result = static_cast<int>(std::sqrt(std::pow((end.x - start.x), 2) + std::pow((end.y - start.y), 2)) * 10);
    return result;
}

