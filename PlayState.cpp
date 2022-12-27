//
// Created by alber on 25/10/2022.
//

#include "PlayState.h"

void PlayState::draw(float dt) const {
    this->game->window.clear(sf::Color::Black);

    this->arenaMap->drawLayer(this->game->window, background);
    this->arenaMap->drawLayer(this->game->window, principal_floor);

    bool isOver = this->arenaMap->isWeaponOverTheWall(*mike);


    //TODO check layer 3d rendering when will be implement the enemies
    if (isOver) {
        this->arenaMap->drawLayer(this->game->window, solid_elements);
        this->arenaMap->drawLayer(this->game->window, layer_3d);
        this->arenaMap->drawLayer(this->game->window, last_layer);
    }

    this->arenaMap->drawLayer(this->game->window, design_elements);

    //draw bonuses
    this->spawner->drawBonuses(this->game->window);

    //draw mike and his weapon
    if (!skinDirection[UP]) {
        this->mike->drawEntity(this->game->window);
        this->mike->weapon->drawWeapon(this->game->window);
    } else {
        this->mike->weapon->drawWeapon(this->game->window);
        this->mike->drawEntity(this->game->window);
    }



    //draw bullets
    this->mike->weapon->drawBullets(this->game->window, dt);

    if (!isOver) {
        this->arenaMap->drawLayer(this->game->window, solid_elements);
        this->arenaMap->drawLayer(this->game->window, layer_3d);
        this->arenaMap->drawLayer(this->game->window, last_layer);
    }

    //draw viewfinder
    this->game->window.draw(viewfinderSprite);

    //draw gui
    mike->gui.drawGui(this->game->window);

}

void PlayState::update(float dt) {
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

    //update bonuses (updates animation and despawn them)
    this->updateBonuses(dt);


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


    mike->directionInput(worldPos, skinDirection);

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
                if (event.key.code == sf::Keyboard::R) {
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

    //mike->directionInput(worldPos, skinDirection);
    normalizedVector = normalize(direction_vector);
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

    this->loadTextures();

    this->spawner = std::unique_ptr<Spawner>(new Spawner(charactersTextures, bonusesTextures, weaponsTextures));

    //create random map
    arenaMap = new ArenaMap(this->whichMap(), this->game->window, mike, charactersTextures.getTextureRef("mike"),
                            weaponsTextures.getTextureRef("handgun"), weaponsTextures.getTextureRef("bullet"),
                            guiTextures);

    viewfinderSprite.setTexture(guiTextures.getTextureRef("viewfinder"));

    this->round = 1;

    this->localPosition = sf::Mouse::getPosition(this->game->window);
    this->worldPos = this->game->window.mapPixelToCoords(localPosition);
}

int PlayState::whichMap() {
    srand(time(NULL));
    int map = rand() % nMap;
    return map;
}

sf::Vector2f PlayState::normalize(sf::Vector2f vector) {
    auto norm = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
    //Prevent division by zero
    if (norm == 0)
        return sf::Vector2f{};
    else
        return vector / norm;
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

    //add here all game textures...
}

sf::Vector2f
PlayState::normalizedViewfinderPos(const sf::Vector2f &viewfinderPos, const GameCharacter &character) {
    sf::Vector2f origin = character.getSpriteCenter();
    sf::Vector2f translation = viewfinderPos - origin;
    return normalize(translation);
}

void PlayState::updateBonuses(float dt) {
    if (!this->spawner->bonuses.empty()) {
        for (int i = 0; i < this->spawner->bonuses.size(); i++) {

            switch (this->spawner->bonuses[i]->getBonusType()) {
                case NEW_WEAPON:
                    if (this->spawner->bonuses[i]->isActiveAnimation)
                        this->spawner->bonuses[i]->currentAnimation.updateNotCyclicalAnimation(dt,
                                                                                               this->spawner->bonuses[i]->isEndedAnimation,
                                                                                               this->spawner->bonuses[i]->isActiveAnimation);
                    if (this->spawner->bonuses[i]->isAbove(this->mike->getSprite().getGlobalBounds()) &&
                        (sf::Keyboard::isKeyPressed(sf::Keyboard::E))) {
                        this->spawner->bonuses[i]->doSpecialAction(*mike);
                        mike->gui.updateWeaponType(weaponsTextures.getTextureRef(mike->weapon->getWeaponName()),
                                                   mike->weapon->currentAnimation.idleFrames[0],
                                                   mike->weapon->hitBox.getSize());
                        mike->gui.updateMagazines(mike->weapon->getMagazine().remainingBullets,
                                                  mike->weapon->getTotalBullets(),
                                                  mike->weapon->isInfiniteBullets());
                        this->spawner->despawnBonus(i);
                        i--;
                    }
                    break;
                case COINS:
                    this->spawner->bonuses[i]->currentAnimation.update(dt);
                    //collect coin
                    if (this->spawner->bonuses[i]->isAbove(this->mike->getSprite().getGlobalBounds())) {
                        //std::cout << "COLLECTED COIN!" << std::endl;
                        this->spawner->bonuses[i]->doSpecialAction(*mike);
                        this->spawner->despawnBonus(i);
                        i--;
                    }
                    break;
                    //TODO add other bonuses updates
                default:
                    std::cerr << "ERROR: SELECTED BONUS NOT EXIST" << std::endl;
                    break;
            }
            if (this->spawner->bonuses.empty()) //these are for prevent memory leak
                break;
            else if (i == -1)
                i = 0;
            if (this->spawner->bonuses[i]->getStayTimer().getElapsedTime() >=
                this->spawner->bonuses[i]->getStayTime()) {
                this->spawner->bonuses[i]->startDespawining();
                this->spawner->bonuses[i]->isActiveAnimation = true;
                if (this->spawner->bonuses[i]->isEndedAnimation || this->spawner->bonuses[i]->isInfiniteAnimation) {
                    this->spawner->despawnBonus(i);
                    std::cout << "DESPAWN" << std::endl;
                }
            }
            if (this->spawner->bonuses.empty())
                break;
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
