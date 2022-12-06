#include "gtest/gtest.h"

#include "../PlayState.h"
#include "MenuFixture.h"

TEST_F (MenuFixture, MapCheck) {
    ASSERT_LE(play->whichMap(), nMap); //check if number of maps is correct
    ASSERT_EQ(play->getArenaMap()->getTotalLayers(), 6); //check if layers are =6
}
