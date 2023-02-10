//
// Created by alber on 31/01/2023.
//
#include "SpawnerFixture.h"

TEST_F(SpawnerFixture, TestEnemiesSpawning) {
    ASSERT_EQ(spawner->getEnemies().size(), 0);
    spawner->spawnWarrior(spawnTile, 80, 1);
    spawner->spawnZombie(spawnTile, 80, 1);
    spawner->spawnArcher(spawnTile, 1);
    spawner->spawnKamikaze(spawnTile, 1);
    EXPECT_EQ(spawner->getEnemies().size(), 4);

}

TEST_F(SpawnerFixture, TestBossSpawning) {
    ASSERT_EQ(spawner->getBosses().size(), 0);
    spawner->spawnBoss(spawnTile, 1);
    EXPECT_EQ(spawner->getBosses().size(), 1);
}

TEST_F(SpawnerFixture, TestEnemiesDespawning) {
    ASSERT_EQ(spawner->getEnemies().size(), 0);
    spawner->spawnWarrior(spawnTile, 80, 1);
    spawner->spawnZombie(spawnTile, 80, 1);
    spawner->spawnArcher(spawnTile, 1);
    spawner->spawnKamikaze(spawnTile, 1);
    EXPECT_EQ(spawner->getEnemies().size(), 4);
    unsigned int remainEnemies = 4;
    ASSERT_EQ(spawner->getEnemies().size(), remainEnemies);
    int index = 2;

    spawner->despawnEnemy(index, remainEnemies);

    EXPECT_EQ(index, 1);
    EXPECT_EQ(remainEnemies, 3);
    EXPECT_EQ(spawner->getEnemies().size(), 3);

}

TEST_F(SpawnerFixture, TestBossDespawning) {
    ASSERT_EQ(spawner->getBosses().size(), 0);
    spawner->spawnBoss(spawnTile, 1);
    EXPECT_EQ(spawner->getBosses().size(), 1);

    unsigned int remainBosses = 1;
    ASSERT_EQ(spawner->getBosses().size(), remainBosses);
    int index = 0;

    spawner->despawnBoss(index, remainBosses);

    EXPECT_EQ(remainBosses, 0);
    EXPECT_EQ(spawner->getBosses().size(), 0);

}

TEST_F(SpawnerFixture, TestBonusSpawning) {
    ASSERT_EQ(spawner->getBonuses().size(), 0);
    spawner->spawnNuke(spawnTile);
    spawner->spawnLifePoints(spawnTile);
    spawner->spawnWeapon(spawnTile);
    spawner->spawnBubble(spawnTile);
    spawner->spawnAmmunition(spawnTile);
    spawner->spawnArmor(spawnTile);
    spawner->spawnIncreasedDamage(spawnTile);
    spawner->spawnCoin({static_cast<float>(spawnTile.x * 32), static_cast<float>(spawnTile.y * 32)}, 1);
    EXPECT_EQ(spawner->getBonuses().size(), 8);
}

TEST_F(SpawnerFixture, TestBonuesDespawning) {
    ASSERT_EQ(spawner->getBonuses().size(), 0);
    spawner->spawnCoin({static_cast<float>(spawnTile.x * 32), static_cast<float>(spawnTile.y * 32)}, 1);
    spawner->spawnBubble(spawnTile);
    EXPECT_EQ(spawner->getBonuses().size(), 2);

    spawner->despawnBonus(0);
    EXPECT_EQ(spawner->getBonuses().size(), 1);
}

TEST_F(SpawnerFixture, TestBonuses) {
    sf::Texture tex;
    std::unique_ptr<Mike> mike = std::unique_ptr<Mike>(new Mike(tex, tex, tex, spawnTile, texManager, {32, 32},
                                                                {32, 32}, 5,
                                                                20, 250));
    unsigned int mikePoints = mike->getPoints();

    ASSERT_EQ(spawner->getBonuses().size(), 0);

    //nuke
    spawner->spawnNuke(spawnTile);
    spawner->getBonuses()[0]->doSpecialAction(*mike);
    EXPECT_GT(mike->getPoints(), mikePoints);
    mikePoints = mike->getPoints();

    //hp
    spawner->spawnLifePoints(spawnTile);
    spawner->getBonuses()[1]->doSpecialAction(*mike);
    EXPECT_GE(mike->getHp(), 20);
    EXPECT_GT(mike->getPoints(), mikePoints);
    mikePoints = mike->getPoints();

    //bubble
    spawner->spawnBubble(spawnTile);
    spawner->getBonuses()[2]->doSpecialAction(*mike);
    EXPECT_EQ(mike->isBubble(), true);
    EXPECT_GT(mike->getPoints(), mikePoints);
    mikePoints = mike->getPoints();

    //armor
    unsigned int mikeArmor = mike->getArmor();
    spawner->spawnArmor(spawnTile);
    spawner->getBonuses()[3]->doSpecialAction(*mike);
    EXPECT_GE(mike->getArmor(), mikeArmor);
    EXPECT_GT(mike->getPoints(), mikePoints);
    mikePoints = mike->getPoints();

    //coins
    unsigned int mikeCoins = mike->getCoins();
    spawner->spawnCoin({static_cast<float>(spawnTile.x * 32), static_cast<float>(spawnTile.y * 32)}, 1);
    spawner->getBonuses()[4]->doSpecialAction(*mike);
    EXPECT_GE(mike->getCoins(), mikeCoins);
    EXPECT_GT(mike->getPoints(), mikePoints);
    mikePoints = mike->getPoints();

}