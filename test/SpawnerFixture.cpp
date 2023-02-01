//
// Created by alber on 31/01/2023.
//

#include "SpawnerFixture.h"

SpawnerFixture::SpawnerFixture() {
    std::vector<std::vector<Node>> nodeMap;
    spawner = std::unique_ptr<Spawner>(
            new Spawner(texManager, texManager, texManager, nodeMap, {32, 32}));
}

SpawnerFixture::~SpawnerFixture() {

}
