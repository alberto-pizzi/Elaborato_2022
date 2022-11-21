//
// Created by alber on 25/10/2022.
//

#include "PlayState.h"

void PlayState::draw(float dt) {
    this->game->window.clear(sf::Color::Black);
    //this->game->window.draw(this->game->background);
    this->arenaMap->drawMap(this->game->window);
    this->mike->drawEntity(this->game->window);
}

void PlayState::update(float dt) {
//TODO insert game implementation
    std::cout << "updating" << std::endl; //TODO remove it (only for debug)
}

void PlayState::handleInput() {

    auto frame_time = frame_clock.restart();
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
                key_states[UP] = key_states[UP] || (event.key.code == sf::Keyboard::W);
                key_states[DOWN] = key_states[DOWN] || (event.key.code == sf::Keyboard::S);
                key_states[LEFT] = key_states[LEFT] || (event.key.code == sf::Keyboard::A);
                key_states[RIGHT] = key_states[RIGHT] || (event.key.code == sf::Keyboard::D);
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::W)
                    key_states[UP] = false;
                else if (event.key.code == sf::Keyboard::S)
                    key_states[DOWN] = false;
                else if (event.key.code == sf::Keyboard::A)
                    key_states[LEFT] = false;
                else if (event.key.code == sf::Keyboard::D)
                    key_states[RIGHT] = false;
                break;

        }
    }
    if ((key_states[LEFT] && key_states[RIGHT]) || (!key_states[LEFT] && !key_states[RIGHT]))
        direction_vector.x = 0.f;
    else if (key_states[LEFT])
        direction_vector.x = -1.f;
    else if (key_states[RIGHT])
        direction_vector.x = 1.f;
    if ((key_states[UP] && key_states[DOWN]) || (!key_states[UP] && !key_states[DOWN]))
        direction_vector.y = 0.f;
    else if (key_states[UP])
        direction_vector.y = -1.f;
    else if (key_states[DOWN])
        direction_vector.y = 1.f;

    if (arenaMap->isLegalMove(direction_vector, *mike))
        mike->moveMike(normalize(direction_vector) * mikeSpeed * frame_time.asSeconds());

}

PlayState::PlayState(Game *game) {
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);
    pos *= 0.5f;
    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);
    std::cout << "I'm PlayState" << std::endl; //TODO remove it (only for debug)
    //random mapList
    this->whichMap();
}

void PlayState::whichMap() {
    srand(time(NULL));
    int map = rand() % nMap;
    //create map
    arenaMap = new ArenaMap(map, this->game->window, mike);
}

sf::Vector2f PlayState::normalize(sf::Vector2f vector) {
    constexpr auto units_in_last_place = 2;
    auto norm = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
    // Prevent division by zero
    if (norm <= std::numeric_limits<float>::epsilon() * norm * units_in_last_place
        || norm < std::numeric_limits<float>::min()) {
        return sf::Vector2f{};
    }
    return vector / norm;
}
