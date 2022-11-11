//
// Created by alber on 25/10/2022.
//

#include "MenuState.h"
#include "PlayState.h"

enum NameButton {
    //this numbers are related with nButtons
    Play = 0,
    Stats = 1,
    Exit = 2,
};

void MenuState::draw(float dt) {
    this->game->window.setView(this->view);

    this->game->window.clear(sf::Color::Black); //remove it
    this->game->window.draw(this->game->background);
    for (int i = 0; i < nButtons; i++)
        this->game->window.draw(mainMenu[i]);

}

void MenuState::update(float dt) {
    //TODO insert menu implementation
}

void MenuState::handleInput() {
    sf::Event event;

    while (this->game->window.pollEvent(event)) {

        switch (event.type) {
            // Close the window
            case sf::Event::Closed:
                game->window.close();
                break;
                // Resize the window
                //FIXME check sizing in menu state (and background)
            case sf::Event::Resized:

                this->view.setSize(event.size.width, event.size.height);
                this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->view));
                this->game->background.setScale(
                        float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
                        float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
                break;

            case sf::Event::KeyPressed: {
                //Take input
                switch (event.key.code) {
                    case sf::Keyboard::Enter:
                        select();
                        break;
                    case sf::Keyboard::W:
                        moveUp();
                        break;
                    case sf::Keyboard::S:
                        moveDown();
                        break;
                }
                break;
            }
                // default:
                //break;
        }
    }
}

void MenuState::loadPlay() {
    this->game->pushState(new PlayState(this->game));
}

MenuState::MenuState(Game *game) {
    //TODO improve menu design (and check this code)
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
    std::string fontFile = "res/fonts/kirbyss.ttf";
    try {
        if (!font.loadFromFile(fontFile))
            throw GameException("Error opening font file", fontFile, false);
    } catch (GameException &e) {}

    //play
    mainMenu[Play].setFont(font);
    mainMenu[Play].setFillColor(sf::Color(102, 0, 0));
    mainMenu[Play].setString("Play");
    mainMenu[Play].setCharacterSize(50);
    mainMenu[Play].setPosition(
            sf::Vector2f(static_cast<float>(this->game->window.getSize().x) / 2 - 50,
                         static_cast<float>(this->game->window.getSize().y) / 2 - 50));

        //stats
        mainMenu[Stats].setFont(font);
        mainMenu[Stats].setFillColor(sf::Color::White);
        mainMenu[Stats].setString("Stats");
        mainMenu[Stats].setCharacterSize(50);
        mainMenu[Stats].setPosition(
                sf::Vector2f(static_cast<float>(this->game->window.getSize().x) / 2 - 50,
                             (static_cast<float>(this->game->window.getSize().y) / 2 - 50) * 1.5));

        //exit
        mainMenu[Exit].setFont(font);
        mainMenu[Exit].setFillColor(sf::Color::White);
        mainMenu[Exit].setString("Exit");
        mainMenu[Exit].setCharacterSize(50);
        mainMenu[Exit].setPosition(
                sf::Vector2f(static_cast<float>(this->game->window.getSize().x) / 2 - 50,
                             (static_cast<float>(this->game->window.getSize().y) / 2 - 50) * 2));

        //if you add more buttons, you must update "nButtons" in the header file

        nButtonSelected = Play;

}

void MenuState::moveUp() {
    if (nButtonSelected - 1 >= -1) {
        mainMenu[nButtonSelected].setFillColor(sf::Color::White);
        nButtonSelected--;
        if (nButtonSelected == -1)
            nButtonSelected = nButtons - 1;
        mainMenu[nButtonSelected].setFillColor(sf::Color(102, 0, 0));
    }
}

void MenuState::moveDown() {
    if (nButtonSelected + 1 <= nButtons) {
        mainMenu[nButtonSelected].setFillColor(sf::Color::White);
        nButtonSelected++;
        if (nButtonSelected == nButtons)
            nButtonSelected = 0;
        mainMenu[nButtonSelected].setFillColor(sf::Color(102, 0, 0));
    }
}

void MenuState::select() {
    switch (nButtonSelected) {
        case Play:
            this->loadPlay();
            break;
        case Stats:
            //TODO implement stats state
            std::cout << "sono stats" << std::endl;
            break;
        case Exit:
            this->game->window.close();
            break;
    }
}
