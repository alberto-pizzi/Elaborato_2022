//
// Created by alber on 21/12/2022.
//

#ifndef ELABORATO_ARENAMAPFIXTURE_H
#define ELABORATO_ARENAMAPFIXTURE_H

#include "gtest/gtest.h"
#include "../Mike.h"
#include "../ArenaMap.h"
#include <memory>

class ArenaMapFixture : public ::testing::Test {
protected:
    ArenaMap *map;
    sf::Context context;
    std::unique_ptr<Mike> mike;
    sf::RenderWindow fakeWindow;
public:
    ArenaMapFixture();

    virtual ~ArenaMapFixture();
};


#endif //ELABORATO_ARENAMAPFIXTURE_H
