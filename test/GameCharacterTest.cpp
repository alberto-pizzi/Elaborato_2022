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
    mike->directionInput({1374, 629}, renderingDirection);
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoUp());
    mike->directionInput({1213, 626}, renderingDirection);
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoUp());

    mike->directionInput({1097, 697}, renderingDirection);
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoLeft());
    mike->directionInput({1145, 859}, renderingDirection);
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoLeft());

    mike->directionInput({1264, 912}, renderingDirection);
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoDown());
    mike->directionInput({1355, 929}, renderingDirection);
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoDown());

    mike->directionInput({1453, 809}, renderingDirection);
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoRight());
    mike->directionInput({1487, 750}, renderingDirection);
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoRight());
}

TEST_F (GameCharacterFixture, TestCorrespondenceBetweenGuiAndMikeHP) {

    //Mike HP must be equal to Gui HP
    ASSERT_EQ(20, mike->getHp());
    mike->gui.updateHealthBar(20);
    EXPECT_EQ(5 * 32, mike->gui.getHealthBar().getTextureRect().width);
    mike->setHp(19);
    mike->gui.updateHealthBar(19);
    unsigned int previousValue = mike->gui.getHealthBar().getTextureRect().width;
    EXPECT_LT(mike->gui.getHealthBar().getTextureRect().width, 5 * 32);
    mike->setHp(18);
    mike->gui.updateHealthBar(18);
    EXPECT_LT(mike->gui.getHealthBar().getTextureRect().width, previousValue);
}

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
    bool skinDirection[4] = {false, false, false, false};

    mike->directionInput({45 * 32, 21 * 32}, skinDirection);
    ASSERT_EQ(skinDirection[RIGHT], true);

    mike->directionInput({46 * 32, 27 * 32}, skinDirection);
    EXPECT_EQ(skinDirection[RIGHT], true);

    mike->directionInput({41 * 32, 20 * 32}, skinDirection);
    EXPECT_EQ(skinDirection[UP], true);

    mike->directionInput({38 * 32, 20 * 32}, skinDirection);
    EXPECT_EQ(skinDirection[UP], true);

    mike->directionInput({35 * 32, 21 * 32}, skinDirection);
    EXPECT_EQ(skinDirection[LEFT], true);

    mike->directionInput({33 * 32, 23 * 32}, skinDirection);
    EXPECT_EQ(skinDirection[LEFT], true);

    mike->directionInput({39 * 32, 35 * 32}, skinDirection);
    EXPECT_EQ(skinDirection[DOWN], true);

    mike->directionInput({42 * 32, 28 * 32}, skinDirection);
    EXPECT_EQ(skinDirection[DOWN], true);
}

TEST_F (GameCharacterFixture, TestBulletsVectorFillingCorrectness) {
    mike->weapon->shoot({1, 0});
    ASSERT_EQ(mike->weapon->getBullets().size(), 1);

    mike->weapon->shoot({1, 0});
    mike->weapon->shoot({1, 0});
    EXPECT_EQ(mike->weapon->getBullets().size(), 3);

}

