//
// Created by Alberto Pizzi on 08/01/23.
//

#include "AI.h"

AI::AI(const std::vector<bool> &mapWithObstacles) {
    this->mapWithObstacles = mapWithObstacles;
}

void AI::updateStartingPoint(sf::Vector2i startingTile) {
    this->startingNode = startingTile;
}
