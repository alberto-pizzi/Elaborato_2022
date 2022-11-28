//
// Created by alber on 25/10/2022.
//

#include "PlayState.h"

void PlayState::draw(float dt) {
    this->game->window.clear(sf::Color::Black);
    //this->game->window.draw(this->game->background);
    this->arenaMap->drawFloorAndDesignElements(this->game->window);
    this->mike->drawEntity(this->game->window);

    this->arenaMap->drawSolidsAnd3DLayers(
            this->game->window); //WARNING: this calling draw 3d and design layers, so it must be THE LAST ONE to be rendered

    this->game->window.draw(viewfinderSprite); //draw viewfinder
}

void PlayState::update(float dt) {
//TODO insert game implementation
    //::cout << "updating" << std::endl; //TODO remove it (only for debug)
}

void PlayState::handleInput() {
    auto frame_time = frame_clock.restart();
    sf::Event event;
    sf::Vector2f normalizedVector;


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
        }
    }

    for (int i = 0; i < 4; i++)
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
    viewfinderSprite.setPosition(sf::Vector2f(worldPos.x - 16, worldPos.y - 16)); // -16 for center

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


    normalizedVector = normalize(direction_vector);
    if (arenaMap->isMovingCorrectly(normalizedVector, *mike, keyStates)) {
        mike->move(normalizedVector, frame_time.asSeconds());
        arenaMap->playerView.setCenter(mike->getPos());
        this->game->window.setView(arenaMap->playerView);
        mike->currentAnimation.update(frame_time.asSeconds());
    }
}

PlayState::PlayState(Game *game) {
    this->game = game;
    std::cout << "I'm PlayState" << std::endl; //TODO remove it (only for debug)
    //random mapList
    this->whichMap();

    std::string fileName = "res/textures/viewfinder.png";
    textureManager.loadTexture("viewfinder", fileName);
    viewfinderSprite.setTexture(textureManager.getTextureRef("viewfinder"));
}

void PlayState::whichMap() {
    srand(time(NULL));
    int map = rand() % nMap;

    //create map
    arenaMap = new ArenaMap(map, this->game->window, mike);
}

sf::Vector2f PlayState::normalize(sf::Vector2f vector) {
    auto norm = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
    //Prevent division by zero
    if (norm == 0)
        return sf::Vector2f{};
    else
        return vector / norm;
}
