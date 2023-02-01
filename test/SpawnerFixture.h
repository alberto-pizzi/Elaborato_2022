//
// Created by alber on 31/01/2023.
//

#ifndef ELABORATO_SPAWNERFIXTURE_H
#define ELABORATO_SPAWNERFIXTURE_H

#include <memory>

#include "../Spawner.h"
#include "gtest/gtest.h"


class SpawnerFixture : public ::testing::Test {
protected:
    sf::Context context;
    std::unique_ptr<Spawner> spawner;
    sf::Vector2i spawnTile = {40, 24};
    TextureManager texManager;
public:
    SpawnerFixture();

    virtual ~SpawnerFixture();
};


#endif //ELABORATO_SPAWNERFIXTURE_H
