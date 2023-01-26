//
// Created by alber on 25/10/2022.
//

#include "MenuState.h"
#include "PlayState.h"
#include "AchievementState.h"

enum NameButton {
    //these numbers are related with nButtons
    Play = 0,
    Stats = 1,
    Exit = 2,
};

void MenuState::draw(float dt) const {
    this->game->window.setView(this->view);
    this->game->window.clear();
    this->game->window.draw(this->game->background);
    for (int i = 0; i < nButtons; i++)
        this->game->window.draw(mainMenu[i]);
}

void MenuState::update(float dt) {
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
        }
    }
}

void MenuState::loadPlay() {
    this->game->pushState(new PlayState(this->game));
}

MenuState::MenuState(Game *game) {
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
    std::string fontFile = "res/fonts/bloody.ttf";
    try {
        if (!font.loadFromFile(fontFile))
            throw GameException("Error opening numbersOrTitlesFont file", fontFile, false);
    } catch (GameException &e) {}

    //play
    mainMenu[Play].setFont(font);
    mainMenu[Play].setFillColor(sf::Color(102, 0, 0));
    mainMenu[Play].setString("Play");
    mainMenu[Play].setCharacterSize(fontSize);
    mainMenu[Play].setPosition(
            sf::Vector2f(
                    static_cast<float>(this->game->window.getSize().x) / 2 - mainMenu[Play].getGlobalBounds().width / 2,
                    static_cast<float>(this->game->window.getSize().y) / 2 - static_cast<float>(fontSize)));

    //stats
    mainMenu[Stats].setFont(font);
    mainMenu[Stats].setFillColor(sf::Color::White);
    mainMenu[Stats].setString("Achievements");
    mainMenu[Stats].setCharacterSize(50);
    mainMenu[Stats].setPosition(
            sf::Vector2f(static_cast<float>(this->game->window.getSize().x) / 2 -
                         mainMenu[Stats].getGlobalBounds().width / 2,
                         (static_cast<float>(this->game->window.getSize().y) / 2 - static_cast<float>(fontSize)) *
                         1.5));

    //exit
    mainMenu[Exit].setFont(font);
    mainMenu[Exit].setFillColor(sf::Color::White);
    mainMenu[Exit].setString("Exit");
    mainMenu[Exit].setCharacterSize(50);
    mainMenu[Exit].setPosition(sf::Vector2f(
            static_cast<float>(this->game->window.getSize().x) / 2 - mainMenu[Exit].getGlobalBounds().width / 2,
            (static_cast<float>(this->game->window.getSize().y) / 2 -
             static_cast<float>(fontSize)) * 2));
    //if you add more buttons, you must updateNotCyclicalAnimation "nButtons" in the header file and unit testing

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
            this->game->pushState(new AchievementState(this->game));
            break;
        case Exit:
            this->game->window.close();
            break;
        default:
            std::cerr << "ERROR: SELECTED BUTTON NOT EXIST" << std::endl;
            break;
    }
}
