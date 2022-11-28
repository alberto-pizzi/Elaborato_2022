#include "gtest/gtest.h"

#include "../PlayState.h"
#include "../MenuState.h"
#include "../Game.h"
#include "../GameState.h"

TEST (PlayState, MapCheck) {
    sf::Context context;
    Game game;
    PlayState *play;
    play = new PlayState(&game);
    ASSERT_LE(play->whichMap(), nMap); //check if number of maps is correct
    EXPECT_LE(play->getArenaMap()->getTotalLayers(), 6); //check if layers are <=6
    delete play;
}

TEST (MenuState, NumButtonsCheck) {
    sf::Context context;
    Game game;
    MenuState *menu;
    menu = new MenuState(&game);
    ASSERT_EQ(3, nButtons);
    delete menu;
}
