//
// Created by alber on 25/10/2022.
//

#include "PlayState.h"

void PlayState::draw(float dt) const {
    this->game->window.clear(sf::Color::Black);

    arenaMap->drawLayer(this->game->window, background);
    arenaMap->drawLayer(this->game->window, principal_floor);

    bool isOver = arenaMap->isWeaponOverTheWall(*mike);


    //TODO check layer 3d rendering when will be implement the enemies
    if (isOver) { //FIXME drawing enemy when mike's weapon is over
        arenaMap->drawLayer(this->game->window, solid_elements);
        arenaMap->drawLayer(this->game->window, layer_3d);
        arenaMap->drawLayer(this->game->window, last_layer);
    }

    arenaMap->drawLayer(this->game->window, design_elements);

    //draw bonuses
    spawner->drawBonuses(this->game->window);

    //draw enemies
    spawner->drawEnemies(this->game->window, startedGameOver, dt);

    //draw mike and his weapon
    if (!gameOver)
        mike->drawEntity(this->game->window, startedGameOver);

    //draw bullets
    mike->weapon->drawBullets(this->game->window, dt);

    if (!isOver) {
        arenaMap->drawLayer(this->game->window, solid_elements);
        arenaMap->drawLayer(this->game->window, layer_3d);
        arenaMap->drawLayer(this->game->window, last_layer);
    }

    //draw viewfinder
    this->game->window.draw(viewfinderSprite);

    //draw gui
    mike->gui.drawGui(this->game->window);

}

void PlayState::update(float dt) {
    if (isPaused) {
        this->game->window.setView(arenaMap->playerView);
        isPaused = false;
    }
    if (gameOver && (gameOverClock.getElapsedTime() >= gameOverTime))
        this->game->popState();
    else if (!gameOver) {
        checkAndUpdateRound();

        //update enemies skin direction based on mike positioning
        //spawner->updateSkinDirection(mike->getSpriteCenter()); //FIXME

        //update all enemies
        updateEnemies(dt);
        checkMikeDead(dt);

        /*
        if ((!isSpawned) && isRandomAbleTo(40,100)){
            this->spawner->spawnWeapon();
            std::cout<<"SPAWNED"<<std::endl;
            isSpawned = true;
        }
         */

        //update active bonuses like bubble, increase damage...
        mike->updateActiveBonuses();
        //update mike skin color when damaged, etc...
        mike->updateCharacterColor();

        //std::cout<<"Active Bonuses: "<<mike->getActualBonuses().size()<<std::endl;

        //update bonuses (updates animation and despawn them)
        updateBonuses(dt);

        //updateNotCyclicalAnimation Gui
        if (mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::ENDED])
            mike->gui.updateMagazines(mike->weapon->getMagazine().remainingBullets, mike->weapon->getTotalBullets(),
                                      mike->weapon->isInfiniteBullets());
        mike->gui.updatePoints(mike->getPoints());
        mike->gui.updateHealthBar(mike->getHp());
    }
}

void PlayState::handleInput() {
    auto frame_time = frame_clock.restart();
    sf::Time shotTimer;
    sf::Event event;
    sf::Vector2f normalizedVector;

    localPosition = sf::Mouse::getPosition(this->game->window);
    worldPos = this->game->window.mapPixelToCoords(localPosition);

    if (!mike->isDead())
        mike->characterSkinDirection(worldPos);

    //viewfinder positioning
    viewfinderSprite.setPosition(sf::Vector2f(worldPos.x - viewfinderSprite.getGlobalBounds().width / 2,
                                              worldPos.y - viewfinderSprite.getGlobalBounds().height / 2));

    while (this->game->window.pollEvent(event)) {
        switch (event.type) {
            // Close the window
            case sf::Event::Closed: {
                this->game->window.close();
                break;
            }
                //Resize the window
            case sf::Event::Resized: {
                gameView.setSize(event.size.width, event.size.height);
                guiView.setSize(event.size.width, event.size.height);
                this->game->background.setPosition(
                        this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
                this->game->background.setScale(
                        float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
                        float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
                break;
            }
            case sf::Event::MouseButtonPressed:
                if ((mike->weapon->getWeaponName() != "assaultRifle") &&
                    (event.mouseButton.button == sf::Mouse::Left)) {
                    if ((!mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::RELOADING]) &&
                        (mike->weapon->thereAreRemainingBullets()) &&
                        (mike->weapon->shotClock.getElapsedTime() >= mike->weapon->getNextShotDelay())) {
                        mike->weapon->shoot(normalizedViewfinderPos(worldPos, *mike));
                        mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::ACTIVE] = true;
                    }
                }
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    isPaused = true;
                    this->game->pushState(new PauseState(this->game));
                } else if (event.key.code == sf::Keyboard::R) {
                    if (mike->weapon->reloadWeapon()) {
                        mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::ACTIVE] = true;
                        mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::ORDERED_RELOADING] = true;
                        mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::RELOADING] = true;
                        std::cout << "RELOAD DONE!" << std::endl;
                    }
                }
                break;
        }
    }

    for (int i = 0; i < 4; i++) //set no input in all keyStates
        mike->keyStates[i] = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        mike->keyStates[UP] = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        mike->keyStates[DOWN] = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        mike->keyStates[LEFT] = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        mike->keyStates[RIGHT] = true;


    //repeated input (automatic fire, assault rifle)
    if ((mike->weapon->getWeaponName() == "assaultRifle") && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
        if ((!mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::RELOADING]) &&
            (mike->weapon->thereAreRemainingBullets()) &&
            (mike->weapon->shotClock.getElapsedTime() >= mike->weapon->getNextShotDelay())) {
            mike->weapon->shoot(normalizedViewfinderPos(worldPos, *mike));
            mike->gui.updateMagazines(mike->weapon->getMagazine().remainingBullets, mike->weapon->getTotalBullets(),
                                      mike->weapon->isInfiniteBullets());
            mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::ACTIVE] = true;
        }

    mike->calculateDirectionVector();

    normalizedVector = mike->normalize(mike->direction_vector);
    if (!arenaMap->collides(mike->futureCharacterPosition(normalizedVector, frame_time.asSeconds()))) {
        mike->move(normalizedVector, frame_time.asSeconds());
        arenaMap->playerView.setCenter(arenaMap->legalViewCenter(mike->getSpriteCenter(), this->game->window.getSize(),
                                                                 {mike->getSprite().getGlobalBounds().width,
                                                                  mike->getSprite().getGlobalBounds().height},
                                                                 arenaMap->playerView.getCenter()));
        this->game->window.setView(arenaMap->playerView);
    }

    //update weapon animation if you make an action as shooting or reloading
    if (!mike->isDead())
        mike->weapon->currentAnimation.updateNotCyclicalAnimation(frame_time.asSeconds(),
                                                                  mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::ENDED],
                                                                  mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::ACTIVE]);

    if (mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::ORDERED_RELOADING] &&
        mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::ENDED]) {
        mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::RELOADING] = false;
        mike->weapon->animationKeyStep[ReloadingAnimationKeySteps::ORDERED_RELOADING] = false;
    }

    mike->setWeaponPosToShouldersPos();

    int cuttingValue = arenaMap->weaponCutXSize(*mike);
    if (cuttingValue != 0) {
        mike->weapon->isCut = true;
        mike->weapon->cutValueX = cuttingValue;
    } else
        mike->weapon->isCut = false;

}

PlayState::PlayState(Game *game) : round(1) {
    this->game = game;

    loadTextures();


    //create random map
    arenaMap = new ArenaMap(whichMap(), this->game->window, mike, charactersTextures.getTextureRef("mike"),
                            weaponsTextures.getTextureRef("handgun"), weaponsTextures.getTextureRef("bullet"),
                            guiTextures, firstRoundStartingTime.asSeconds());

    spawner = std::unique_ptr<Spawner>(
            new Spawner(charactersTextures, bonusesTextures, weaponsTextures, arenaMap->nodeMap,
                        {arenaMap->getTileSizeX(), arenaMap->getTileSizeY()}));


    viewfinderSprite.setTexture(guiTextures.getTextureRef("viewfinder"));

    randomPercentageDice.setFaces(100 - 1);

    localPosition = sf::Mouse::getPosition(this->game->window);
    worldPos = this->game->window.mapPixelToCoords(localPosition);

    //hide mouse cursor
    this->game->window.setMouseCursorVisible(false);
}

int PlayState::whichMap() {
    srand(time(NULL));
    int map = rand() % nMap;
    return map;
}

ArenaMap *PlayState::getArenaMap() const {
    return arenaMap;
}

PlayState::~PlayState() {
    delete arenaMap;
}

void PlayState::loadTextures() {
    //load character textures
    charactersTextures.loadTexture("mike", "res/textures/no_hands_mike.png");
    charactersTextures.loadTexture("shield", "res/textures/shield.png");
    charactersTextures.loadTexture("zombie", "res/textures/zombie.png");
    charactersTextures.loadTexture("archer", "res/textures/archer.png");

    //load gui textures
    guiTextures.loadTexture("viewfinder", "res/textures/viewfinder.png");
    guiTextures.loadTexture("healthBar", "res/textures/progressbar.png");

    //load weapons (general, also spawning weapon)
    weaponsTextures.loadTexture("handgun", "res/textures/handgun_hand.png");
    weaponsTextures.loadTexture("assaultRifle", "res/textures/assault_rifle.png");
    weaponsTextures.loadTexture("shotgun", "res/textures/shotgun.png");
    weaponsTextures.loadTexture("bow", "res/textures/bow.png");

    //load bullets
    weaponsTextures.loadTexture("bullet", "res/textures/bullet.png");
    weaponsTextures.loadTexture("arrow", "res/textures/arrow.png");

    //load bonuses textures
    bonusesTextures.loadTexture("weaponBox", "res/textures/bonus_weapons.png");
    bonusesTextures.loadTexture("coin", "res/textures/coin.png");
    bonusesTextures.loadTexture("bonusesBox", "res/textures/bonuses.png");

    //add here all game textures...
}

sf::Vector2f
PlayState::normalizedViewfinderPos(const sf::Vector2f &viewfinderPos, const GameCharacter &character) {
    sf::Vector2f origin = character.getSpriteCenter();
    sf::Vector2f translation = viewfinderPos - origin;
    return mike->normalize(translation);
}

void PlayState::updateBonuses(float dt) {
    if (!spawner->bonuses.empty()) {
        for (int i = 0; i < spawner->bonuses.size(); i++) {

            switch (spawner->bonuses[i]->getBonusType()) {
                case NEW_WEAPON:
                    if (spawner->bonuses[i]->isActiveAnimation)
                        spawner->bonuses[i]->currentAnimation.updateNotCyclicalAnimation(dt,
                                                                                         spawner->bonuses[i]->isEndedAnimation,
                                                                                         spawner->bonuses[i]->isActiveAnimation);
                    if (spawner->bonuses[i]->isAbove(mike->getSprite().getGlobalBounds()) &&
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::E))) {
                        spawner->bonuses[i]->doSpecialAction(*mike);
                        mike->gui.updateWeaponType(weaponsTextures.getTextureRef(mike->weapon->getWeaponName()),
                                                   mike->weapon->currentAnimation.idleFrames[0],
                                                   mike->weapon->hitBox.getSize());
                        mike->gui.updateMagazines(mike->weapon->getMagazine().remainingBullets,
                                                  mike->weapon->getTotalBullets(),
                                                  mike->weapon->isInfiniteBullets());
                        spawner->despawnBonus(i);
                        i--;
                    }
                    break;
                    /*
                case AMMUNITION:
                    spawner->bonuses[i]->currentAnimation.update(dt);
                    //collect ammo
                    if (spawner->bonuses[i]->isAbove(mike->getSprite().getGlobalBounds())) {
                        spawner->bonuses[i]->doSpecialAction(*mike);
                        spawner->despawnBonus(i);
                        i--;
                        mike->gui.updateMagazines(mike->weapon->getMagazine().remainingBullets,
                                                  mike->weapon->getTotalBullets(),
                                                  mike->weapon->isInfiniteBullets());
                    }
                    break;
                    */
                case COINS:
                    spawner->bonuses[i]->currentAnimation.update(dt);
                    //collect coin
                    if (spawner->bonuses[i]->isAbove(mike->getSprite().getGlobalBounds())) {
                        //std::cout << "COLLECTED COIN!" << std::endl;
                        spawner->bonuses[i]->doSpecialAction(*mike);
                        spawner->despawnBonus(i);
                        i--;
                    } else if (spawner->bonuses[i]->getStayTimer().getElapsedTime() >=
                               spawner->bonuses[i]->getStayTime()) {
                        spawner->despawnBonus(i);
                        i--;
                    }
                    break;
                    /*
                case PROTECTION_BUBBLE:
                    spawner->bonuses[i]->currentAnimation.update(dt);
                    //collect protection bubble
                    if (spawner->bonuses[i]->isAbove(mike->getSprite().getGlobalBounds())) {
                        spawner->bonuses[i]->doSpecialAction(*mike);
                        mike->addToOwnBonuses(PROTECTION_BUBBLE, spawner->bonuses[i]->getDuration());
                        spawner->despawnBonus(i);
                        i--;
                    }
                    break;
                     */
                case NUKE:
                    if (spawner->bonuses[i]->isActiveAnimation)
                        spawner->bonuses[i]->currentAnimation.updateNotCyclicalAnimation(dt,
                                                                                         spawner->bonuses[i]->isEndedAnimation,
                                                                                         spawner->bonuses[i]->isActiveAnimation);
                    if (spawner->bonuses[i]->isAbove(mike->getSprite().getGlobalBounds())) {
                        spawner->bonuses[i]->doSpecialAction(*mike);
                        spawner->bonuses.clear(); //kill all enemies //FIXME death animations
                        spawner->despawnBonus(i);
                        i--;
                    }
                    break;
                    //the next bonuses have the same functioning
                case INCREASED_DAMAGE:
                case AMMUNITION:
                case ARMOR:
                case LIFE_POINTS:
                case PROTECTION_BUBBLE:
                    if (spawner->bonuses[i]->isActiveAnimation)
                        spawner->bonuses[i]->currentAnimation.updateNotCyclicalAnimation(dt,
                                                                                         spawner->bonuses[i]->isEndedAnimation,
                                                                                         spawner->bonuses[i]->isActiveAnimation);
                    if (spawner->bonuses[i]->isAbove(mike->getSprite().getGlobalBounds())) {
                        spawner->bonuses[i]->doSpecialAction(*mike);
                        spawner->despawnBonus(i);
                        i--;
                    }
                    break;
                    //TODO add other bonuses updates
                default:
                    std::cerr << "ERROR: SELECTED BONUS NOT EXIST" << std::endl;
                    break;
            }
            if (spawner->bonuses.empty()) //these are for prevent memory leak
                break;
            else if (i == -1)
                i = 0;
            if ((!spawner->bonuses[i]->isInfiniteAnimation) && (spawner->bonuses[i]->getStayTimer().getElapsedTime() >=
                                                                spawner->bonuses[i]->getStayTime())) {
                spawner->bonuses[i]->startDespawining();
                spawner->bonuses[i]->isActiveAnimation = true;
                if (spawner->bonuses[i]->isEndedAnimation) {
                    spawner->despawnBonus(i);
                    i--;
                    std::cout << "DESPAWN" << std::endl;
                }
            }
            if (spawner->bonuses.empty())
                break;
        }

    }
}

void PlayState::initRound() {
    float sum = 0;
    float tmpPercentage, tmpNEnemies;
    bool extraEnemy = false;

    if (round % bossRoundFrequency == 0) {
        if (round <= 25)
            remainBosses = round / bossRoundFrequency;
        else
            remainBosses = bossRoundFrequency + 1;
        remainEnemies = baseNumber;
    } else {
        //growing enemies
        remainBosses = 0;
        remainEnemies = baseNumber +
                        (incrementableNumber * (static_cast<unsigned int>(std::log2(static_cast<float>(round))) + 1));
    }


    if (round < 30) {
        //FIXME fix all percentages for each round

        //warrior
        totEnemiesForType[WARRIOR].typePercentage = static_cast<float>(randomPercentageDice.casualNumber(15, 25));
        tmpNEnemies = (totEnemiesForType[WARRIOR].typePercentage / 100.f) * static_cast<float>(remainEnemies);
        if (!isInteger(tmpNEnemies))
            extraEnemy = true;
        totEnemiesForType[WARRIOR].numberOfEnemies = static_cast<unsigned int>(tmpNEnemies);
        sum += totEnemiesForType[WARRIOR].typePercentage;

        //kamikaze
        totEnemiesForType[KAMIKAZE].typePercentage = static_cast<float>(randomPercentageDice.casualNumber(5, 15));
        tmpNEnemies = (totEnemiesForType[KAMIKAZE].typePercentage / 100.f) * static_cast<float>(remainEnemies);
        if (!isInteger(tmpNEnemies))
            extraEnemy = true;
        totEnemiesForType[KAMIKAZE].numberOfEnemies = static_cast<unsigned int>(tmpNEnemies);
        sum += totEnemiesForType[KAMIKAZE].typePercentage;

        //zombie (most probable enemy must be the last)
        totEnemiesForType[ZOMBIE].typePercentage = 100 - sum;
        tmpNEnemies = (totEnemiesForType[ZOMBIE].typePercentage / 100.f) * static_cast<float>(remainEnemies);
        if (!isInteger(tmpNEnemies))
            extraEnemy = true;
        totEnemiesForType[ZOMBIE].numberOfEnemies = static_cast<unsigned int>(tmpNEnemies);

    }

/*
    std::cout << "ZOMBIE %: " << totEnemiesForType[ZOMBIE].numberOfEnemies << std::endl;
    std::cout << "WARRIOR %: " << totEnemiesForType[WARRIOR].numberOfEnemies << std::endl;
    std::cout << "KAMIKAZE %: " << totEnemiesForType[KAMIKAZE].numberOfEnemies << std::endl << std::endl;

    //std::cout << "SUM: " << sum << std::endl;
    */

    if (extraEnemy) {
        extraEnemy = false;
        totEnemiesForType[ZOMBIE].numberOfEnemies++;
    }

    //spawnEachTypeOfEnemies(); //FIXME uncomment this and remove the lines below
    //TODO implement crescent hitProbability

    //spawner->spawnZombie(arenaMap->randomPassableTile());
    //spawner->spawnZombie(arenaMap->randomPassableTile());
    //spawner->spawnZombie(arenaMap->randomPassableTile());
    //spawner->spawnZombie(arenaMap->randomPassableTile());
    //spawner->spawnZombie(arenaMap->randomPassableTile());
    //spawner->spawnArcher(arenaMap->randomPassableTile());
    spawner->spawnZombie(arenaMap->randomPassableTile(), 80);

    remainEnemies = 1;


    std::cout << "VECTOR SIZE: " << spawner->enemies.size() << " REMAINING: " << remainEnemies << std::endl;
    //for (int i = 0; i < remainBosses; i++) //TODO add boss spawn


}

void PlayState::updateEnemies(float dt) {

    for (int i = 0; i < spawner->enemies.size(); i++) {
        sf::RectangleShape obstacle;

        if (spawner->enemies[i]->isDeathAnimationActive)
            spawner->enemies[i]->currentAnimation.updateNotCyclicalAnimation(dt,
                                                                             spawner->enemies[i]->isDeathAnimationEnded,
                                                                             spawner->enemies[i]->isDeathAnimationActive);

        spawner->updateEnemy(*mike, dt, i, arenaMap->collides(spawner->enemies[i]->futureCharacterPosition(
                spawner->enemies[i]->normalize(
                        spawner->characterPositionRelativeToAnother(*spawner->enemies[i], *mike)),
                dt), obstacle), obstacle); //update animation and movement
        mike->weapon->updateBullets(arenaMap, *(spawner->enemies[i]));
        if (spawner->enemies[i]->weapon) {
            spawner->enemies[i]->setWeaponPosToShouldersPos();

            spawner->enemies[i]->weapon->updateBullets(arenaMap, *mike);
            if (!mike->isDead())
                spawner->enemies[i]->weapon->currentAnimation.updateNotCyclicalAnimation(dt,
                                                                                         spawner->enemies[i]->weapon->animationKeyStep[ReloadingAnimationKeySteps::ENDED],
                                                                                         spawner->enemies[i]->weapon->animationKeyStep[ReloadingAnimationKeySteps::ACTIVE]);
        }
        spawner->enemies[i]->updateCharacterColor();
        updateViewfinderColor(*spawner->enemies[i]);

        if (spawner->enemies[i]->isDead()) {

            spawner->enemies[i]->startDespawning();
            spawner->enemies[i]->isDeathAnimationActive = true;
            if (spawner->enemies[i]->isDeathAnimationEnded) {
                spawner->spawnCoin(spawner->enemies[i]->getSpriteCenter(), spawner->enemies[i]->getCoins());
                spawner->despawnEnemy(i, remainEnemies);
            }

            if (spawner->enemies.empty())
                break;
        } else if ((spawner->enemies[i]->isAbleToHit(*mike, spawner->hitDice)) ||
                   (spawner->enemies[i]->getCharacterType() == ARCHER)) { //FIXME random hit chance and improve archer
            if (spawner->enemies[i]->getCharacterType() == KAMIKAZE) {
                spawner->enemies[i]->areaHit(spawner->enemies);
            } else {
                //TODO implement hit chance
                spawner->enemies[i]->hit(*mike);
            }
        }

    }
}

bool PlayState::isRoundEnded() const {
    if ((remainEnemies == 0) && (remainBosses == 0))
        return true;
    else
        return false;
}

bool PlayState::isInteger(float n) const {
    int x = n;
    float temp2 = n - x;
    if (temp2 > 0)
        return false;
    return true;
}

void PlayState::spawnEachTypeOfEnemies() {
    for (int i = 0; i < totEnemiesForType[ZOMBIE].numberOfEnemies; i++) {
        spawner->spawnZombie(arenaMap->randomPassableTile(), 0); //FIXME random enemy type and hit prob
    }

    for (int i = 0; i < totEnemiesForType[WARRIOR].numberOfEnemies; i++) {
        spawner->spawnWarrior(arenaMap->randomPassableTile(), 0); //FIXME random enemy type and hit prob
    }

    for (int i = 0; i < totEnemiesForType[KAMIKAZE].numberOfEnemies; i++) {
        spawner->spawnKamikaze(arenaMap->randomPassableTile()); //FIXME random enemy type and hit prob
    }

    //TODO add archer
}

void PlayState::checkAndUpdateRound() {
    if ((round == 1) && (roundSleepClock.getElapsedTime() <= firstRoundStartingTime) && (!firstSpawnDone)) {
        mike->gui.updateCountdown(firstRoundStartingTime.asSeconds(), false);

    } else if ((round == 1) && (!firstSpawnDone)) {
        mike->gui.setCountdownVisible(false);
        //initialize first round (with enemies, etc..)
        initRound();
        firstSpawnDone = true;
    }

    if (endRoundCountStarted && (roundSleepClock.getElapsedTime() >= afterRoundSleepTime)) {
        endRoundCountStarted = false;
        mike->gui.setCountdownVisible(false);
        initRound();

    } else if (isRoundEnded() && (!endRoundCountStarted)) {
        endRoundCountStarted = true;
        round++;
        mike->gui.updateRound(round);
        roundSleepClock.restart();
        mike->gui.setCountdownVisible(true);
        mike->gui.updateCountdown(afterRoundSleepTime.asSeconds(), true);
    } else {
        mike->gui.updateCountdown(roundSleepClock.getElapsedTime().asSeconds(), false);
    }
}

void PlayState::updateViewfinderColor(const Enemy &enemy) {
    if (enemy.isHit1())
        viewfinderSprite.setColor(enemy.getHitColor());
    else
        viewfinderSprite.setColor(sf::Color::White);
}

void PlayState::checkMikeDead(float dt) {
    if (mike->isDead()) {
        startedGameOver = true;
        mike->startDespawning();
        mike->isDeathAnimationActive = true;
        mike->gui.updateGameOver(true);
        mike->currentAnimation.updateNotCyclicalAnimation(dt, mike->isDeathAnimationEnded,
                                                          mike->isDeathAnimationActive);
        if (mike->isDeathAnimationEnded) {
            if (!gameOver) {
                gameOverClock.restart();
                gameOver = true;
            }
        }
    }
}

/*
bool PlayState::isRandomAbleTo(float percentage, int nRolls) {

    float restPercentage = 1 - (percentage / 100);

    int chance = dice.roll(nRolls);

    if (static_cast<float>(chance) >= (static_cast<float>(nRolls * dice.getFaces())) * restPercentage)
        return true;
    return false;
}
*/
