//
// Created by alber on 09/01/2023.
//

#include "Node.h"

Node::Node(int x, int y, bool walkable, const std::vector<std::shared_ptr<Node>> adjacentNodes)
        : tile({x, y}), walkable(walkable), gCost(0), hCost(0), fCost(0),
          parent(nullptr) {

}

void Node::expandNeighbors(const std::vector<std::vector<Node>> &map) {
    adjacentNodes.clear();

    // check north tile
    if (tile.y > 0) {
        std::shared_ptr<Node> northTile = std::make_shared<Node>(map[tile.y - 1][tile.x]);
        if (northTile->walkable)
            adjacentNodes.push_back(northTile);
    }
    // check east tile
    if (tile.x < map[0].size() - 1) {
        std::shared_ptr<Node> eastTile = std::make_shared<Node>(map[tile.y][tile.x + 1]);
        if (eastTile->walkable)
            adjacentNodes.push_back(eastTile);

    }
    // check south tile
    if (tile.y < map.size() - 1) {
        std::shared_ptr<Node> southTile = std::make_shared<Node>(map[tile.y + 1][tile.x]);
        if (southTile->walkable)
            adjacentNodes.push_back(southTile);
    }
    // check west tile
    if (tile.x > 0) {
        std::shared_ptr<Node> westTile = std::make_shared<Node>(map[tile.y][tile.x - 1]);
        if (westTile->walkable)
            adjacentNodes.push_back(westTile);

    }

    // check north-east tile
    if (tile.y > 0 && tile.x < map[0].size() - 1) {
        std::shared_ptr<Node> northEastTile = std::make_shared<Node>(map[tile.y - 1][tile.x + 1]);
        if (northEastTile->walkable)
            adjacentNodes.push_back(northEastTile);

    }

    // check south-east tile
    if (tile.y < map.size() - 1 && tile.x < map[0].size() - 1) {
        std::shared_ptr<Node> southEasyTile = std::make_shared<Node>(map[tile.y + 1][tile.x + 1]);
        if (southEasyTile->walkable)
            adjacentNodes.push_back(southEasyTile);

    }

    // check north-west tile
    if (tile.x > 0 && tile.y > 0) {
        std::shared_ptr<Node> northWestTile = std::make_shared<Node>(map[tile.y - 1][tile.x - 1]);
        if (northWestTile->walkable)
            adjacentNodes.push_back(northWestTile);

    }

    // check south-west tile
    if (tile.x > 0 && tile.y < map[0].size() - 1) {
        std::shared_ptr<Node> southWestTile = std::make_shared<Node>(map[tile.y + 1][tile.x - 1]);
        if (southWestTile->walkable)
            adjacentNodes.push_back(southWestTile);

    }


}

void Node::setParent(const std::shared_ptr<Node> &parentNode) {
    parent = parentNode;
}

const sf::Vector2i &Node::getTile() const {
    return tile;
}

bool Node::isWalkable() const {
    return walkable;
}
