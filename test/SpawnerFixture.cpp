//
// Created by alber on 31/01/2023.
//

#include "SpawnerFixture.h"

SpawnerFixture::SpawnerFixture() {
    std::vector<std::vector<Node>> fakeNodeMap;
    spawner = std::unique_ptr<Spawner>(
            new Spawner(fakeTexManager, fakeTexManager, fakeTexManager, fakeNodeMap, {32, 32}));
}

SpawnerFixture::~SpawnerFixture() {

}
