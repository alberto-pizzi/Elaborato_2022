//
// Created by alber on 21/12/2022.
//

#include "ArenaMapFixture.h"

ArenaMapFixture::~ArenaMapFixture() {
    delete map;
}

ArenaMapFixture::ArenaMapFixture() {
    map = new ArenaMap(0, fakeWindow, mike);
}
