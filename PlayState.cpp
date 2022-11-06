//
// Created by alber on 25/10/2022.
//

#include "PlayState.h"

void PlayState::draw(float dt) {
    this->game->window.clear(sf::Color::Black);
    this->game->window.draw(this->game->background);
    //this->game->window.draw(this->arenaMap->drawMap());
    //this->arenaMap->drawMap(this->game->window, 2);
}

void PlayState::update(float dt) {
//TODO insert game implementation
    std::cout << "sono update" << std::endl;
}

void PlayState::handleInput() {
    sf::Event event;

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
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    this->game->window.close();
                break;
        }
    }


}

PlayState::PlayState(Game *game) {
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);
    pos *= 0.5f;
    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);
    //random mapList
    std::cout << "Sono playstate" << std::endl;

    this->whichMap();

}

void PlayState::whichMap() {
    //FIXME add other maps (90x45 tiles)
    //WARNING: for adding other maps, you must update nMap/loadMap and enum in ArenaMap.h
    int nMap = 1;
    srand(time(NULL));
    int map = rand() % nMap;

    //create mapList

    arenaMap = new ArenaMap(map);
}
