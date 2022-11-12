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
#include "Mike.h"

class Spawner {
private:
    std::unique_ptr<Mike> mike;
    std::vector<std::unique_ptr<GameCharacter>> enemies;
    std::vector<std::unique_ptr<Bonus>> bonuses;
    std::vector<std::unique_ptr<GameCharacter>> bosses;
public:
    const std::vector<std::unique_ptr<GameCharacter>> &getEnemies() const;

    const std::vector<std::unique_ptr<Bonus>> &getBonuses() const;

    const std::vector<std::unique_ptr<GameCharacter>> &getBosses() const;

    void spawnMike();


};


#endif //ELABORATO_SPAWNER_H
