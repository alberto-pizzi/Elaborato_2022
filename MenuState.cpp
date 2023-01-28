//
// Created by alber on 25/10/2022.
//

#include "MenuState.h"
#include "PlayState.h"
#include "AchievementState.h"



void MenuState::draw(float dt) const {
    this->game->window.setView(this->view);
    this->game->window.clear();
    this->game->window.draw(this->game->background);
    this->game->window.draw(rightCharacter);
    this->game->window.draw(leftCharacter);
    for (int i = 0; i < nButtons; i++) {
        this->game->window.draw(menuButton[i]);
        this->game->window.draw(textMenu[i]);
    }
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
    loadTextures();

    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
    std::string fontFile = "res/fonts/fffforwa.ttf";
    try {
        if (!font.loadFromFile(fontFile))
            throw GameException("Error opening numbersOrTitlesFont file", fontFile, false);
    } catch (GameException &e) {}

    //set box
    for (int i = 0; i < nButtons; i++)
        menuButton[i].setTexture(textureManager.getTextureRef("button"));

    menuButton[Play].setPosition(sf::Vector2f(
            static_cast<float>(this->game->window.getSize().x) / 2 - menuButton[Play].getGlobalBounds().width / 2,
            static_cast<float>(this->game->window.getSize().y) / 2 - menuButton[Play].getGlobalBounds().height / 2));
    menuButton[Stats].setPosition(sf::Vector2f(
            static_cast<float>(this->game->window.getSize().x) / 2 - menuButton[Stats].getGlobalBounds().width / 2,
            menuButton[Play].getPosition().y + menuButton[Play].getGlobalBounds().height + buttonDistance));
    menuButton[Exit].setPosition(sf::Vector2f(
            static_cast<float>(this->game->window.getSize().x) / 2 - menuButton[Exit].getGlobalBounds().width / 2,
            menuButton[Stats].getPosition().y + menuButton[Stats].getGlobalBounds().height + buttonDistance));

    //set characters

    rightCharacter.setTexture(textureManager.getTextureRef("mike"));
    rightCharacter.setTextureRect(
            {characterTextureSize.x, 1 * characterTextureSize.y, characterTextureSize.x, characterTextureSize.y});
    leftCharacter.setTexture(textureManager.getTextureRef("mike"));
    leftCharacter.setTextureRect(
            {characterTextureSize.x, 2 * characterTextureSize.y, characterTextureSize.x, characterTextureSize.y});

    sf::Vector2f charactersScale = {10, 10};
    rightCharacter.setScale(charactersScale);
    leftCharacter.setScale(charactersScale);

    rightCharacter.setPosition(
            sf::Vector2f(menuButton[Play].getPosition().x + buttonDistance + menuButton[Play].getGlobalBounds().width,
                         menuButton[Play].getPosition().y));
    leftCharacter.setPosition(
            sf::Vector2f(menuButton[Play].getPosition().x - buttonDistance - leftCharacter.getGlobalBounds().width,
                         menuButton[Play].getPosition().y));

    //set texts
    for (int i = 0; i < nButtons; i++) {
        textMenu[i].setFont(font);
        textMenu[i].setCharacterSize(fontSize);
        textMenu[i].setFillColor(sf::Color::White);
    }

    //play
    textMenu[Play].setFillColor(selectedColor);
    textMenu[Play].setString("Play");
    textMenu[Play].setPosition(
            sf::Vector2f(
                    menuButton[Play].getPosition().x + menuButton[Play].getGlobalBounds().width / 2 -
                    textMenu[Play].getGlobalBounds().width / 2,
                    menuButton[Play].getPosition().y + menuButton[Play].getGlobalBounds().height / 2 -
                    textMenu[Play].getGlobalBounds().height / 2 + alignValue));

    //stats
    textMenu[Stats].setString("Achievements");
    textMenu[Stats].setPosition(
            sf::Vector2f(
                    menuButton[Stats].getPosition().x + menuButton[Stats].getGlobalBounds().width / 2 -
                    textMenu[Stats].getGlobalBounds().width / 2,
                    menuButton[Stats].getPosition().y + menuButton[Stats].getGlobalBounds().height / 2 -
                    textMenu[Stats].getGlobalBounds().height / 2 + alignValue));

    //exit
    textMenu[Exit].setString("Exit");
    textMenu[Exit].setPosition(
            sf::Vector2f(
                    menuButton[Exit].getPosition().x + menuButton[Exit].getGlobalBounds().width / 2 -
                    textMenu[Exit].getGlobalBounds().width / 2,
                    menuButton[Exit].getPosition().y + menuButton[Exit].getGlobalBounds().height / 2 -
                    textMenu[Exit].getGlobalBounds().height / 2 + alignValue));

    //if you add more buttons, you must updateNotCyclicalAnimation "nButtons" in the header file and unit testing
    nButtonSelected = Play;
}

void MenuState::moveUp() {
    if (nButtonSelected - 1 >= -1) {
        textMenu[nButtonSelected].setFillColor(sf::Color::White);
        nButtonSelected--;
        if (nButtonSelected == -1)
            nButtonSelected = nButtons - 1;
        textMenu[nButtonSelected].setFillColor(sf::Color(102, 0, 0));
    }
}

void MenuState::moveDown() {
    if (nButtonSelected + 1 <= nButtons) {
        textMenu[nButtonSelected].setFillColor(sf::Color::White);
        nButtonSelected++;
        if (nButtonSelected == nButtons)
            nButtonSelected = 0;
        textMenu[nButtonSelected].setFillColor(sf::Color(102, 0, 0));
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

void MenuState::loadTextures() {
    textureManager.loadTexture("button", "res/textures/menu_button.png");
    textureManager.loadTexture("mike", "res/textures/mike.png");
}
