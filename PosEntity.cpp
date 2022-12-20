//
// Created by alber on 20/12/2022.
//
#include "PosEntity.h"

PosEntity::PosEntity() = default;

void PosEntity::updateGlobalPosition(sf::FloatRect newGlobalPos) {
    this->pos = newGlobalPos;
    this->spriteCenter = {newGlobalPos.left + newGlobalPos.width / 2, newGlobalPos.top + newGlobalPos.height / 2};
}

const sf::FloatRect &PosEntity::getPos() const {
    return pos;
}

const sf::Vector2f &PosEntity::getSpriteCenter() const {
    return spriteCenter;
}
