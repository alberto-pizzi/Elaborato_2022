//
// Created by alber on 25/10/2022.
//

#include "PlayState.h"

void PlayState::draw(float dt) const {
    this->game->window.clear(sf::Color::Black);
    //this->game->window.draw(this->game->background);
    this->arenaMap->drawFloorAndDesignElements(this->game->window);
    if (!isUp) {
        this->mike->drawEntity(this->game->window);
        this->mike->weapon->drawWeapon(this->game->window);
    } else {
        this->mike->weapon->drawWeapon(this->game->window);
        this->mike->drawEntity(this->game->window);
    }

    this->arenaMap->drawSolidsAnd3DLayers(
            this->game->window); //WARNING: this calling draw 3d and design layers, so it must be THE LAST ONE to be rendered

    this->game->window.draw(viewfinderSprite); //draw viewfinder

    mike->gui.drawGui(this->game->window);

}

void PlayState::update(float dt) {
    //TODO insert game implementation
    //std::cout << "updating" << std::endl; //TODO remove it (only for debug)
    //updateNotCyclicalAnimation Gui
    if (isEnded)
        mike->gui.updateMagazines(mike->weapon->getMagazine().remainingBullets, mike->weapon->getTotalBullets(),
                                  mike->weapon->isInfiniteBullets());
    mike->gui.updatePoints(mike->getPoints());
    mike->gui.updateHealthBar(mike->getHp());
}

void PlayState::handleInput() {
    auto frame_time = frame_clock.restart();
    sf::Event event;
    sf::Vector2f normalizedVector;
    if (mike->nextAttackTimeCount >=
        50) //set limits to prevent overflow during counting (these numbers represent wide margin of prevention)
        mike->nextAttackTimeCount = 20;
    mike->nextAttackTimeCount += frame_time.asSeconds();
    //std::cout << "Time: " << mike->nextAttackTimeCount << std::endl; //FIXME only for debug
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
                if (event.mouseButton.button ==
                    sf::Mouse::Left) { //FIXME review this when assault rifle implementation is done (for shooting animation and reload)
                    if ((!isActiveAnimation) && (mike->weapon->thereAreRemainingBullets()) &&
                        (mike->nextAttackTimeCount >= mike->weapon->getNextShotDelay())) {
                        mike->weapon->shoot();
                        mike->nextAttackTimeCount = 0;
                        isActiveAnimation = true;
                    }
                }
                break;
            case sf::Event::KeyReleased: //single input
                if (event.key.code == sf::Keyboard::R) {
                    std::cout << "RELOAD!" << std::endl;
                    if (mike->weapon->reloadWeapon()) { //FIXME add correct texture animation
                        isActiveAnimation = true;
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


    sf::Vector2i localPosition = sf::Mouse::getPosition(this->game->window);
    sf::Vector2f worldPos = this->game->window.mapPixelToCoords(localPosition);
    viewfinderSprite.setPosition(sf::Vector2f(worldPos.x - viewfinderSprite.getGlobalBounds().width / 2,
                                              worldPos.y - viewfinderSprite.getGlobalBounds().height / 2));

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

    mike->directionInput(worldPos, isUp);
    normalizedVector = normalize(direction_vector);
    if (arenaMap->isMovingCorrectly(normalizedVector, *mike)) {
        mike->move(normalizedVector, frame_time.asSeconds());
        arenaMap->playerView.setCenter(arenaMap->legalViewCenter(mike->getPos(), this->game->window.getSize(),
                                                                 {mike->getSprite().getGlobalBounds().width,
                                                                  mike->getSprite().getGlobalBounds().height},
                                                                 arenaMap->playerView.getCenter()));
        this->game->window.setView(arenaMap->playerView);
        mike->currentAnimation.update(frame_time.asSeconds());
    }

    //update weapon animation if you make an action as shooting or reloading
    mike->weapon->currentAnimation.updateNotCyclicalAnimation(frame_time.asSeconds(), isEnded, isActiveAnimation);

    mike->setWeaponPosToShouldersPos();

}

PlayState::PlayState(Game *game) {
    this->game = game;

    //create random map
    arenaMap = new ArenaMap(this->whichMap(), this->game->window, mike);

    loadTextures();
    viewfinderSprite.setTexture(textureManager.getTextureRef("viewfinder"));

    this->round = 1;
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
    //load viewfinder
    textureManager.loadTexture("viewfinder", "res/textures/viewfinder.png");

    //load weapons (general, also spawning weapon)
    textureManager.loadTexture("handgun", "res/textures/handgun_hand.png"); //FIXME

    textureManager.loadTexture("assaultRifle", "res/textures/assault_rifle.png"); //FIXME

    textureManager.loadTexture("shotgun", "res/textures/shotgun.png"); //FIXME

}
