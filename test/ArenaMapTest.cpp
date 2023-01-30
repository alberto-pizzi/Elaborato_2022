//
// Created by alber on 21/12/2022.
//
#include "gtest/gtest.h"

#include "../GameCharacter.h"
#include "ArenaMapFixture.h"

TEST_F (ArenaMapFixture, TestBulletsDirection) {
    //set basic spawned
    mike->setSpritePos({40 * 32, 24 * 32});
    mike->updateGlobalPosition(mike->getSprite().getGlobalBounds());

    sf::Vector2f origin = mike->getSpriteCenter();
    sf::Vector2f viewfinderPos = {60 * 32, 11 * 32};
    sf::Vector2f translation = viewfinderPos - origin;
    auto norm = std::sqrt((translation.x * translation.x) + (translation.y * translation.y));

    mike->weapon->setNextShotDelay(sf::seconds(0));

    mike->weapon->shoot(translation / norm);
    ASSERT_EQ(mike->weapon->getBullets().size(), 1);
    //mike->weapon->getBullets().begin()->get()->move(mike->weapon->getBullets().begin()->get()->getBulletDir(), dt);
    sf::Vector2f oldBulletPos;
    oldBulletPos.x = mike->weapon->getBullets().begin()->get()->getBulletSprite().getPosition().x;
    oldBulletPos.y = mike->weapon->getBullets().begin()->get()->getBulletSprite().getPosition().y;

    mike->weapon->getBullets().begin()->get()->move(mike->weapon->getBullets().begin()->get()->getBulletDir(), 1);

    sf::Vector2f currentVelocity;
    currentVelocity.x = mike->weapon->getBullets().begin()->get()->getBulletDir().x *
                        mike->weapon->getBullets().begin()->get()->getBulletSpeed();
    currentVelocity.y = mike->weapon->getBullets().begin()->get()->getBulletDir().y *
                        mike->weapon->getBullets().begin()->get()->getBulletSpeed();

    EXPECT_EQ(oldBulletPos + currentVelocity,
              mike->weapon->getBullets().begin()->get()->getBulletSprite().getPosition());
}

TEST_F (ArenaMapFixture, TestBulletCollisionsOnMap) {

    ASSERT_EQ(map->collidesWithSolidsOrBounds({56 * 32, 13 * 32, 19, 8}), true);
    EXPECT_EQ(map->collidesWithSolidsOrBounds({44 * 32, 17 * 32, 19, 8}), false);
    EXPECT_EQ(map->collidesWithSolidsOrBounds({27 * 32, 33 * 32, 19, 8}), false);
}

