//
// Created by alber on 10/02/2023.
//
#include "AchievementFixture.h"

TEST_F(AchievementFixture, TestObserver) {

    std::unique_ptr<Mike> mike = std::unique_ptr<Mike>(
            new Mike(mikeTex, weaponTex, bulletTex, spawnTile, textureManager, {32, 32},
                     {32, 32}, 5,
                     20, 250));

    ASSERT_NE(AchievementManager::getInstance()->achievements.size(), 0);
    ASSERT_GT(AchievementManager::getInstance()->achievements.begin()->second->getAchievements().size(), 0);

    ASSERT_GT(
            AchievementManager::getInstance()->achievements.begin()->second->getAchievements().begin()->get()->getTargetProgress(),
            0);
    ASSERT_EQ(
            AchievementManager::getInstance()->achievements.begin()->second->getAchievements().begin()->get()->getActualProgress(),
            0);

    //kill enemy (zombie, for example)
    mike->incrementKills(ZOMBIE);

    //check increment into observer
    EXPECT_GT(
            AchievementManager::getInstance()->achievements.begin()->second->getAchievements().begin()->get()->getActualProgress(),
            0);

}