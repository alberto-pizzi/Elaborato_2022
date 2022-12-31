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
    if (isOver) {
        arenaMap->drawLayer(this->game->window, solid_elements);
        arenaMap->drawLayer(this->game->window, layer_3d);
        arenaMap->drawLayer(this->game->window, last_layer);
    }

    arenaMap->drawLayer(this->game->window, design_elements);

    //draw bonuses
    spawner->drawBonuses(this->game->window);

    //draw enemies
    spawner->drawEnemies(this->game->window);

    //draw mike and his weapon
    if (!mike->skinDirection[UP]) {
        mike->drawEntity(this->game->window);
        mike->weapon->drawWeapon(this->game->window);
    } else {
        mike->weapon->drawWeapon(this->game->window);
        mike->drawEntity(this->game->window);
    }

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

    //update enemies skin direction based on mike positioning
    spawner->updateSkinDirection(mike->getSpriteCenter()); //FIXME




    for (int i = 0; i < spawner->enemies.size(); i++) {
        if (spawner->enemies[i]->isAbleToHit(*mike)) {
            mike->setIsHit(true);
            mike->hitColorClock.restart();
            mike->receiveDamage(2);
        }
    }

    //TODO insert game implementation
    //std::cout << "updating" << std::endl; //TODO remove it (only for debug)
    //std::cout<<"SIZE: "<<mike->weapon->getBullets().size()<<std::endl;

    /*
    if ((!isSpawned) && isRandomAbleTo(40,100)){
        this->spawner->spawnWeapon();
        std::cout<<"SPAWNED"<<std::endl;
        isSpawned = true;
    }
     */


    mike->updateActiveBonuses(); //update active bonuses like bubble, increase damage...
    mike->updateCharacterColor();

    //std::cout<<"Active Bonuses: "<<mike->getActualBonuses().size()<<std::endl;

    //update enemies
    spawner->updateEnemies(*mike, dt);

    //update bonuses (updates animation and despawn them)
    updateBonuses(dt);


    mike->weapon->updateBullets(arenaMap);
    //updateNotCyclicalAnimation Gui
    if (mike->weapon->animationKeyStep[AnimationKeySteps::ENDED])
        mike->gui.updateMagazines(mike->weapon->getMagazine().remainingBullets, mike->weapon->getTotalBullets(),
                                  mike->weapon->isInfiniteBullets());
    mike->gui.updatePoints(mike->getPoints());
    mike->gui.updateHealthBar(mike->getHp());
}

void PlayState::handleInput() {
    auto frame_time = frame_clock.restart();
    sf::Time shotTimer;
    sf::Event event;
    sf::Vector2f normalizedVector;

    localPosition = sf::Mouse::getPosition(this->game->window);
    worldPos = this->game->window.mapPixelToCoords(localPosition);


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
                    if ((!mike->weapon->animationKeyStep[AnimationKeySteps::RELOADING]) &&
                        (mike->weapon->thereAreRemainingBullets()) &&
                        (mike->weapon->shotClock.getElapsedTime() >= mike->weapon->getNextShotDelay())) {
                        mike->weapon->shoot(normalizedViewfinderPos(worldPos, *mike));
                        mike->weapon->animationKeyStep[AnimationKeySteps::ACTIVE] = true;
                    }
                }
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    isPaused = true;
                    this->game->pushState(new PauseState(this->game));
                } else if (event.key.code == sf::Keyboard::R) {
                    if (mike->weapon->reloadWeapon()) {
                        mike->weapon->animationKeyStep[AnimationKeySteps::ACTIVE] = true;
                        mike->weapon->animationKeyStep[AnimationKeySteps::ORDERED_RELOADING] = true;
                        mike->weapon->animationKeyStep[AnimationKeySteps::RELOADING] = true;
                        std::cout << "RELOAD DONE!" << std::endl;
                    }
                }
                break;
        }
    }

    for (int i = 0; i < 4; i++) //set no input in all keyStates
        keyStates[i] = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        keyStates[UP] = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        keyStates[DOWN] = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        keyStates[LEFT] = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        keyStates[RIGHT] = true;


    //repeated input (automatic fire, assault rifle)
    if ((mike->weapon->getWeaponName() == "assaultRifle") && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
        if ((!mike->weapon->animationKeyStep[AnimationKeySteps::RELOADING]) &&
            (mike->weapon->thereAreRemainingBullets()) &&
            (mike->weapon->shotClock.getElapsedTime() >= mike->weapon->getNextShotDelay())) {
            mike->weapon->shoot(normalizedViewfinderPos(worldPos, *mike));
            mike->gui.updateMagazines(mike->weapon->getMagazine().remainingBullets, mike->weapon->getTotalBullets(),
                                      mike->weapon->isInfiniteBullets());
            mike->weapon->animationKeyStep[AnimationKeySteps::ACTIVE] = true;
        }

    if ((keyStates[LEFT] && keyStates[RIGHT]) || (!keyStates[LEFT] && !keyStates[RIGHT]))
        direction_vector.x = 0.f;
    else if (keyStates[LEFT])
        direction_vector.x = -1.f;
    else if (keyStates[RIGHT])
        direction_vector.x = 1.f;
    if ((keyStates[UP] && keyStates[DOWN]) || (!keyStates[UP] && !keyStates[DOWN]))
        direction_vector.y = 0.f;
    else if (keyStates[UP])
        direction_vector.y = -1.f;
    else if (keyStates[DOWN])
        direction_vector.y = 1.f;

    //mike->characterSkinDirection(worldPos, enemySkinDirection);
    normalizedVector = mike->normalize(direction_vector);
    if (arenaMap->isMovingCorrectly(normalizedVector, *mike)) {
        mike->move(normalizedVector, frame_time.asSeconds());
        arenaMap->playerView.setCenter(arenaMap->legalViewCenter(mike->getSpriteCenter(), this->game->window.getSize(),
                                                                 {mike->getSprite().getGlobalBounds().width,
                                                                  mike->getSprite().getGlobalBounds().height},
                                                                 arenaMap->playerView.getCenter()));
        this->game->window.setView(arenaMap->playerView);
        mike->currentAnimation.update(frame_time.asSeconds());
    }



    //update weapon animation if you make an action as shooting or reloading
    mike->weapon->currentAnimation.updateNotCyclicalAnimation(frame_time.asSeconds(),
                                                              mike->weapon->animationKeyStep[AnimationKeySteps::ENDED],
                                                              mike->weapon->animationKeyStep[AnimationKeySteps::ACTIVE]);

    if (mike->weapon->animationKeyStep[AnimationKeySteps::ORDERED_RELOADING] &&
        mike->weapon->animationKeyStep[AnimationKeySteps::ENDED]) {
        mike->weapon->animationKeyStep[AnimationKeySteps::RELOADING] = false;
        mike->weapon->animationKeyStep[AnimationKeySteps::ORDERED_RELOADING] = false;
    }

    mike->setWeaponPosToShouldersPos();

    int cuttingValue = arenaMap->weaponCutXSize(*mike);
    if (cuttingValue != 0) {
        mike->weapon->isCut = true;
        mike->weapon->cutValueX = cuttingValue;
    } else
        mike->weapon->isCut = false;

}

PlayState::PlayState(Game *game) {
    this->game = game;

    loadTextures();

    spawner = std::unique_ptr<Spawner>(new Spawner(charactersTextures, bonusesTextures, weaponsTextures));

    //create random map
    arenaMap = new ArenaMap(whichMap(), this->game->window, mike, charactersTextures.getTextureRef("mike"),
                            weaponsTextures.getTextureRef("handgun"), weaponsTextures.getTextureRef("bullet"),
                            guiTextures);

    viewfinderSprite.setTexture(guiTextures.getTextureRef("viewfinder"));

    round = 1;

    localPosition = sf::Mouse::getPosition(this->game->window);
    worldPos = this->game->window.mapPixelToCoords(localPosition);

    //TODO remove them
    //spawner->spawnEnemies();
    //spawner->spawnNuke();
    //spawner->spawnWeapon();
    //spawner->spawnAmmunition();
    //spawner->spawnBubble();
    //spawner->spawnIncreasedDamage();
    //spawner->spawnCoin();
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

    //load gui textures
    guiTextures.loadTexture("viewfinder", "res/textures/viewfinder.png");
    guiTextures.loadTexture("healthBar", "res/textures/progressbar.png");

    //load weapons (general, also spawning weapon)
    weaponsTextures.loadTexture("handgun", "res/textures/handgun_hand.png");
    weaponsTextures.loadTexture("assaultRifle", "res/textures/assault_rifle.png");
    weaponsTextures.loadTexture("shotgun", "res/textures/shotgun.png");

    //load bullets
    weaponsTextures.loadTexture("bullet", "res/textures/bullet.png");

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
            if (spawner->bonuses[i]->getStayTimer().getElapsedTime() >=
                spawner->bonuses[i]->getStayTime()) {
                spawner->bonuses[i]->startDespawining();
                spawner->bonuses[i]->isActiveAnimation = true;
                if (spawner->bonuses[i]->isEndedAnimation || spawner->bonuses[i]->isInfiniteAnimation) {
                    spawner->despawnBonus(i);
                    std::cout << "DESPAWN" << std::endl;
                }
            }
            if (spawner->bonuses.empty())
                break;
        }

    }
}

void PlayState::calculateTotalEnemiesPerRound() {
    if (round % bossRoundFrequency == 0) {
        remainBosses = 1;
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
