#include "gtest/gtest.h"

#include "../GameCharacter.h"
#include "GameCharacterFixture.h"
#include "../Gui.h"


TEST_F(GameCharacterFixture, TestXYMove) {
    mike->move({0, 1}, 1);
    EXPECT_EQ(40 * 32 + 24, mike->getSpriteCenter().x);
    EXPECT_EQ(24 * 32 + 24 + 250, mike->getSpriteCenter().y);
}

TEST_F(GameCharacterFixture, TestDiagonalMove) {
    mike->move({-1, 1}, 1);
    EXPECT_LE(mike->getSpriteCenter().x, 40 * 32 + 24 - 176);
    EXPECT_GE(mike->getSpriteCenter().x, 40 * 32 + 24 - 177);

    EXPECT_LE(mike->getSpriteCenter().y, 24 * 32 + 24 + 177);
    EXPECT_GE(mike->getSpriteCenter().y, 24 * 32 + 24 + 176);
}

TEST_F(GameCharacterFixture, TestDirectionMouseInputAnimation) {
    //test Mike body direction when mouse exceeds bisects (+- 45°) of all quadrants
    bool renderingDirection[4];
    mike->characterSkinDirection({1374, 629});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoUp());
    mike->characterSkinDirection({1213, 626});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoUp());

    mike->characterSkinDirection({1097, 697});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoLeft());
    mike->characterSkinDirection({1145, 859});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoLeft());

    mike->characterSkinDirection({1264, 912});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoDown());
    mike->characterSkinDirection({1355, 929});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoDown());

    mike->characterSkinDirection({1453, 809});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoRight());
    mike->characterSkinDirection({1487, 750});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoRight());
}
/*
TEST_F (GameCharacterFixture, TestCorrespondenceBetweenGuiAndMikeHP) { //FIXME

    //Mike HP must be equal to Gui HP
    ASSERT_EQ(20, mike->getHp());
    mike->gui.updateHealthBar(20);
    EXPECT_EQ(5 * 32, mike->gui.getHealthBar().getLocalBounds().width);
    mike->setHp(19);
    mike->gui.updateHealthBar(19);
    unsigned int previousValue = mike->gui.getHealthBar().getLocalBounds().width;
    EXPECT_LT(mike->gui.getHealthBar().getLocalBounds().width, 5 * 32);
    mike->setHp(18);
    mike->gui.updateHealthBar(18);
    EXPECT_LT(mike->gui.getHealthBar().getLocalBounds().width, previousValue);
}
 */

TEST_F (GameCharacterFixture, TestCorrespondenceBetweenGuiAndMikePoints) {
    std::string stringPoints;
    //Mike points must be equal to Gui Points
    ASSERT_EQ("0000000000", mike->gui.getPointsDisplayed());

    mike->setPoints(600);
    stringPoints = "0000000" + std::to_string(mike->getPoints());
    mike->gui.updatePoints(600);
    EXPECT_EQ(stringPoints, mike->gui.getPointsDisplayed());

    mike->setPoints(999999999);
    stringPoints = "0" + std::to_string(mike->getPoints());
    mike->gui.updatePoints(999999999);
    EXPECT_EQ(stringPoints, mike->gui.getPointsDisplayed());
}

TEST_F (GameCharacterFixture, TestMagazineAfterShot) {

    mike->weapon->setNextShotDelay(sf::seconds(0));
    //handgun magazine test
    ASSERT_EQ(12, mike->weapon->getMagazine().remainingBullets);
    ASSERT_EQ(12, mike->weapon->getMagazine().totalCapacity);

    mike->weapon->shoot({1, 0});
    EXPECT_EQ(12 - 1, mike->weapon->getMagazine().remainingBullets);
    EXPECT_EQ(12, mike->weapon->getMagazine().totalCapacity);

    mike->weapon->setMagazine(1, 12);
    mike->weapon->shoot({1, 0});
    EXPECT_EQ(0, mike->weapon->getMagazine().remainingBullets);
    EXPECT_EQ(12, mike->weapon->getMagazine().totalCapacity);

    mike->weapon->reloadWeapon();
    ASSERT_EQ(12, mike->weapon->getMagazine().totalCapacity);
    EXPECT_EQ(mike->weapon->getMagazine().remainingBullets, mike->weapon->getMagazine().totalCapacity);
}

TEST_F (GameCharacterFixture, TestSkinSideCorrectnessnDuringMouseInput) {

    mike->characterSkinDirection({45 * 32, 21 * 32});
    ASSERT_EQ(mike->skinDirection[RIGHT], true);

    mike->characterSkinDirection({46 * 32, 27 * 32});
    EXPECT_EQ(mike->skinDirection[RIGHT], true);

    mike->characterSkinDirection({41 * 32, 20 * 32});
    EXPECT_EQ(mike->skinDirection[UP], true);

    mike->characterSkinDirection({38 * 32, 20 * 32});
    EXPECT_EQ(mike->skinDirection[UP], true);

    mike->characterSkinDirection({35 * 32, 21 * 32});
    EXPECT_EQ(mike->skinDirection[LEFT], true);

    mike->characterSkinDirection({33 * 32, 23 * 32});
    EXPECT_EQ(mike->skinDirection[LEFT], true);

    mike->characterSkinDirection({39 * 32, 35 * 32});
    EXPECT_EQ(mike->skinDirection[DOWN], true);

    mike->characterSkinDirection({42 * 32, 28 * 32});
    EXPECT_EQ(mike->skinDirection[DOWN], true);
}

TEST_F (GameCharacterFixture, TestBulletsVectorFillingCorrectness) {
    mike->weapon->setNextShotDelay(sf::seconds(0));
    mike->weapon->shoot({1, 0});
    ASSERT_EQ(mike->weapon->getBullets().size(), 1);

    mike->weapon->shoot({1, 0});
    mike->weapon->shoot({1, 0});
    EXPECT_EQ(mike->weapon->getBullets().size(), 3);
}

TEST_F(GameCharacterFixture, TestEnemyHits) {
    PlayState *play;
    Game game;
    play = new PlayState(&game);

    //test zombie
    play->getSpawner()->spawnZombie(spawnTile, 100, 1);
    ASSERT_EQ(play->getSpawner()->getEnemies().size(), 1);
    float actualHP = mike->getHp();
    std::vector<std::unique_ptr<Enemy>> emptyVector;
    play->getSpawner()->getEnemies().begin()->get()->hit(*mike, emptyVector);
    EXPECT_LT(mike->getHp(), actualHP);

    mike->setHp(mike->getDefaultHp());

    //test warrior
    play->getSpawner()->spawnWarrior(spawnTile, 100, 1);
    ASSERT_EQ(play->getSpawner()->getEnemies().size(), 2);
    actualHP = mike->getHp();
    play->getSpawner()->getEnemies()[1]->hit(*mike, emptyVector);
    EXPECT_LT(mike->getHp(), actualHP);

    mike->setHp(mike->getDefaultHp());

    //test archer
    play->getSpawner()->spawnArcher(spawnTile, 1);
    ASSERT_EQ(play->getSpawner()->getEnemies().size(), 3);
    actualHP = mike->getHp();
    play->getSpawner()->getEnemies()[2]->weapon->setNextShotDelay(sf::seconds(0));
    play->getSpawner()->getEnemies()[2]->hit(*mike, emptyVector);
    EXPECT_GT(play->getSpawner()->getEnemies()[2]->weapon->getBullets().size(), 0);

    mike->setHp(mike->getDefaultHp());

    //test boss
    play->getSpawner()->spawnBoss(spawnTile, 1);
    ASSERT_EQ(play->getSpawner()->getBosses().size(), 1);
    actualHP = mike->getHp();
    play->getSpawner()->getBosses().begin()->get()->weapon->setNextShotDelay(sf::seconds(0));
    play->getSpawner()->getBosses().begin()->get()->weapon->shoot({1, 1});
    EXPECT_GT(play->getSpawner()->getBosses().begin()->get()->weapon->getBullets().size(), 0);

    delete play;
}

