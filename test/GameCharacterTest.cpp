#include "gtest/gtest.h"

#include "../GameCharacter.h"
#include "GameCharacterFixture.h"
#include "../Gui.h"


TEST_F(GameCharacterFixture, TestXYMove) {
    mike->move({0, 1}, 1);
    EXPECT_EQ(40 * 32 + 16, mike->getPos().x);
    EXPECT_EQ(24 * 32 + 16 + 250, mike->getPos().y);
}

TEST_F(GameCharacterFixture, TestDiagonalMove) {
    //FIXME epsilon (near)
    mike->move({-1, 1}, 1);
    EXPECT_LE(mike->getPos().x, 40 * 32 + 16 - 176);
    EXPECT_GE(mike->getPos().x, 40 * 32 + 16 - 177);

    EXPECT_LE(mike->getPos().y, 24 * 32 + 16 + 177);
    EXPECT_GE(mike->getPos().y, 24 * 32 + 16 + 176);
}

TEST_F(GameCharacterFixture, TestDirectionMouseInput) {
    //test Mike body direction when mouse exceeds bisects (+- 45°) of all quadrants
    mike->directionInput({1374, 629});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoUp());
    mike->directionInput({1213, 626});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoUp());

    mike->directionInput({1097, 697});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoLeft());
    mike->directionInput({1145, 859});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoLeft());

    mike->directionInput({1264, 912});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoDown());
    mike->directionInput({1355, 929});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoDown());

    mike->directionInput({1453, 809});
    EXPECT_EQ(mike->currentAnimation.frames, mike->getGoRight());
    mike->directionInput({1487, 750});
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
    stringPoints = "00000000" + std::to_string(mike->getPoints());
    mike->gui.updatePoints(600);
    EXPECT_EQ(stringPoints, mike->gui.getPointsDisplayed());

    mike->setPoints(999999999);
    stringPoints = "0" + std::to_string(mike->getPoints());
    mike->gui.updatePoints(999999999);
    EXPECT_EQ(stringPoints, mike->gui.getPointsDisplayed());
}

