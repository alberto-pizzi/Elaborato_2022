#include "gtest/gtest.h"

#include "../PlayState.h"
#include "StateFixture.h"

TEST_F (StateFixture, MapCheck) {
    ASSERT_LE(play->whichMap(), nMap); //check if number of maps is correct
    ASSERT_EQ(play->getArenaMap()->getTotalLayers(), 6); //check if layers are =6
}

TEST_F (StateFixture, RoundCheck) {
    ASSERT_EQ(play->getRound(), 1);

    play->initRound();

    play->setRemainBosses(0);
    play->setRemainEnemies(0);

    play->checkAndUpdateRound();

    EXPECT_GT(play->getRound(), 1);
}

TEST_F (StateFixture, BossSpawning) {
    unsigned int round = 5, remainBosses = 1;
    int bossIndex = 0;
    ASSERT_EQ(play->getRound(), 1);

    play->setRound(round);
    play->initRound();
    ASSERT_EQ(play->getRound(), round);
    EXPECT_EQ(play->getSpawner()->getBosses().size(), 1);
    EXPECT_EQ(play->getRemainBosses(), 1);
    play->getSpawner()->despawnBoss(bossIndex, remainBosses);
    ASSERT_EQ(play->getSpawner()->getBosses().size(), 0);

    round = 6;
    play->setRound(round);
    play->initRound();
    ASSERT_EQ(play->getRound(), round);
    EXPECT_EQ(play->getSpawner()->getBosses().size(), 0);
    EXPECT_EQ(play->getRemainBosses(), 0);

    round = 10;
    play->setRound(round);
    play->initRound();
    ASSERT_EQ(play->getRound(), round);
    EXPECT_EQ(play->getSpawner()->getBosses().size(), 1);
    EXPECT_EQ(play->getRemainBosses(), 1);

}

TEST_F(StateFixture, TestAchivementLoadingFromFile) {
    AchievementState *achievementState;
    achievementState = new AchievementState(&game);
    //checks correct map filling
    if (AchievementManager::getInstance())
        ASSERT_EQ(achievementState->getAchievements().size(), 0);
    achievementState->loadAchievements();
    ASSERT_GT(achievementState->getAchievements().size(), 0);
    EXPECT_GT(achievementState->getAchievements().begin()->second->getAchievements().size(), 0);


}