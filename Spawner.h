//
// Created by alber on 12/11/2022.
//

#ifndef ELABORATO_SPAWNER_H
#define ELABORATO_SPAWNER_H

#include <memory>
#include <vector>
#include <iostream>

#include "GameCharacter.h"
#include "Bonus.h"
#include "NewWeapon.h"
#include "TextureManager.h"


class Spawner {
private:
    friend class PlayState;

    std::vector<std::unique_ptr<GameCharacter>> enemies;
    std::vector<std::unique_ptr<Bonus>> bonuses;
    std::vector<std::unique_ptr<GameCharacter>> bosses;
    TextureManager enemiesTextures;
    TextureManager bonusesTextures;
    TextureManager weaponsTextures;
public:
    Spawner(const TextureManager &enemiesTextures, const TextureManager &bonusesTextures,
            const TextureManager &weaponsTextures);

    const std::vector<std::unique_ptr<GameCharacter>> &getEnemies() const;

    const std::vector<std::unique_ptr<Bonus>> &getBonuses() const;

    const std::vector<std::unique_ptr<GameCharacter>> &getBosses() const;

    void spawnWeapon();

    void despawnBonus(int &bonusIndex);

    void drawBonuses(sf::RenderWindow &window);

};


#endif //ELABORATO_SPAWNER_H
