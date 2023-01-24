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
    closedList.clear();

//add starting node into open list
    std::shared_ptr<Node> startNode = std::make_shared<Node>(startTile.x, startTile.y, true);
    startNode->gCost = 0;
    startNode->hCost = calculateManhattanDistance(startTile, targetTile);
    startNode->fCost = startNode->gCost + startNode->hCost;
    openList.push_back(startNode);

// loop until path is found or no more nodes to evaluate
    while (!openList.empty()) {
        // find node with lowest fCost in openList
        std::shared_ptr<Node> currentNode = openList[0];
        int currentIndex = 0;
        for (int i = 1; i < openList.size(); ++i) {
            if (openList[i]->fCost < currentNode->fCost) {
                currentNode = openList[i];
                currentIndex = i;
            }
        }

        // remove current node from open list and add it to closed list
        openList.erase(openList.begin() + currentIndex);
        closedList.push_back(currentNode);


        // check if current node is the target node, if so return path
        if (currentNode->tile == targetTile)
            return reconstructPath(startNode, currentNode);



        // expand neighbors of current node
        currentNode->expandNeighbors(map);

        // calculate costs of neighbors and add them to open list if not already in it
        for (int j = 0; j < currentNode->adjacentNodes.size(); j++) {
            std::shared_ptr<Node> adjacentNode = currentNode->adjacentNodes[j];
            if (isInsideClosedList(adjacentNode))
                continue;

            if (checkForObliqueShortcuts(currentNode, adjacentNode))
                continue;

            if (!isInsideOpenList(adjacentNode)) {
                adjacentNode->gCost =
                        currentNode->gCost + calculateManhattanDistance(currentNode->tile, adjacentNode->tile);
                adjacentNode->hCost = calculateManhattanDistance(adjacentNode->tile, targetTile);
                adjacentNode->fCost = adjacentNode->gCost + adjacentNode->hCost;
                adjacentNode->parent = currentNode;
                openList.push_back(adjacentNode);
            } else {
// check if using the current gCost to get to this node is better than the previous one
                int newGCost = currentNode->gCost +
                               calculateManhattanDistance(currentNode->tile, currentNode->adjacentNodes[j]->tile);
                if (newGCost < currentNode->adjacentNodes[j]->gCost) {
                    currentNode->adjacentNodes[j]->gCost = newGCost;
                    currentNode->adjacentNodes[j]->fCost =
                            currentNode->adjacentNodes[j]->gCost + currentNode->adjacentNodes[j]->hCost;
                    currentNode->adjacentNodes[j]->parent = currentNode;


                    // if the adjacent node is not in the open list, add it
                    if (!isInsideOpenList(currentNode->adjacentNodes[j])) {
                        openList.push_back(currentNode->adjacentNodes[j]);
                    }
                }
            }
        }
    }

// if no path was found, return an empty vector
    return {};
}

int AI::calculateManhattanDistance(sf::Vector2i startTile, sf::Vector2i targetTile) const {
    return std::abs(targetTile.x - startTile.x) + std::abs(targetTile.y - startTile.y);
}

std::vector<Node>
AI::reconstructPath(const std::shared_ptr<Node> &startNode, std::shared_ptr<Node> &endNode) {
    std::vector<Node> path;
    std::shared_ptr<Node> currentNode = endNode;

    while (currentNode != startNode) {
        path.push_back(*currentNode);
        currentNode = currentNode->parent;
    }

    std::reverse(path.begin(), path.end());

    return path;
}

bool AI::isInsideClosedList(const std::shared_ptr<Node> &currentNode) {
    for (auto &closedNode: closedList) {
        if (currentNode->tile == closedNode->tile)
            return true;
    }
    return false;
}

bool AI::isInsideOpenList(const std::shared_ptr<Node> &currentNode) {
    for (auto &openNode: openList) {
        if (currentNode->tile == openNode->tile)
            return true;
    }
    return false;
}

int AI::calculateGCost(sf::Vector2i start, sf::Vector2i end) const {
    int result = static_cast<int>(std::sqrt(std::pow((end.x - start.x), 2) + std::pow((end.y - start.y), 2)) * 10);
    return result;
}

void AI::calculateNodeCosts(const std::shared_ptr<Node> &currentNode, sf::Vector2i targetTile) {
    for (int i = 0; i < currentNode->adjacentNodes.size(); i++) {
        //update neighbors G cost
        currentNode->adjacentNodes[i]->gCost = calculateGCost(currentNode->tile, currentNode->adjacentNodes[i]->tile);
        //update neighbors H cost
        currentNode->adjacentNodes[i]->hCost = calculateManhattanDistance(currentNode->adjacentNodes[i]->tile,
                                                                          targetTile);
        //update neighbors F cost
        currentNode->adjacentNodes[i]->fCost =
                currentNode->adjacentNodes[i]->hCost + currentNode->adjacentNodes[i]->gCost;
    }
}

bool AI::checkForObliqueShortcuts(std::shared_ptr<Node> currentNode, std::shared_ptr<Node> adjacentNode) {
    // check if the adjacent node is diagonal to the current node
    if (currentNode->tile.x != adjacentNode->tile.x && currentNode->tile.y != adjacentNode->tile.y) {
        // check if the nodes orthogonally adjacent to the adjacent node are blocked
        sf::Vector2i leftNode(adjacentNode->tile.x - 1, adjacentNode->tile.y);
        sf::Vector2i rightNode(adjacentNode->tile.x + 1, adjacentNode->tile.y);
        sf::Vector2i upNode(adjacentNode->tile.x, adjacentNode->tile.y - 1);
        sf::Vector2i downNode(adjacentNode->tile.x, adjacentNode->tile.y + 1);
        if (map[leftNode.y][leftNode.x].isWalkable() ||
            map[rightNode.y][rightNode.x].isWalkable() ||
            map[upNode.y][upNode.x].isWalkable() ||
            map[downNode.y][downNode.x].isWalkable()) {
            return true;
        }
    }
    return false;
}