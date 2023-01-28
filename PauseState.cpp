//
// Created by Alberto Pizzi on 30/12/22.
//

#include "PauseState.h"



void PauseState::draw(float dt) const {
    this->game->window.setView(this->view);
    this->game->window.clear();
    this->game->window.draw(this->game->background);
    this->game->window.draw(pauseMenu);
    for (int i = 0; i < nButtons; i++) {
        this->game->window.draw(menuButton[i]);
        this->game->window.draw(textMenu[i]);
    }
}

void PauseState::update(float dt) {
}

void PauseState::handleInput() {
    sf::Event event;

    while (this->game->window.pollEvent(event)) {

        switch (event.type) {
            // Close the window
            case sf::Event::Closed:
                //save achievements
                AchievementManager::getInstance()->saveAchievements();
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
                    case sf::Keyboard::Escape:
                        this->game->popState();
                        break;
                }
                break;
            }
        }
    }
}

PauseState::PauseState(Game *game) {

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
    for (int i = 0; i < nButtonsPause; i++)
        menuButton[i].setTexture(this->game->textureManager.getTextureRef("button"));

    menuButton[Resume].setPosition(sf::Vector2f(
            static_cast<float>(this->game->window.getSize().x) / 2 - menuButton[Resume].getGlobalBounds().width / 2,
            static_cast<float>(this->game->window.getSize().y) / 2 - menuButton[Resume].getGlobalBounds().height / 2));
    menuButton[Achievements].setPosition(sf::Vector2f(
            static_cast<float>(this->game->window.getSize().x) / 2 -
            menuButton[Achievements].getGlobalBounds().width / 2,
            menuButton[Resume].getPosition().y + menuButton[Resume].getGlobalBounds().height + buttonDistance));
    menuButton[Exit].setPosition(sf::Vector2f(
            static_cast<float>(this->game->window.getSize().x) / 2 - menuButton[Exit].getGlobalBounds().width / 2,
            menuButton[Achievements].getPosition().y + menuButton[Achievements].getGlobalBounds().height +
            buttonDistance));


    //set texts
    for (int i = 0; i < nButtonsPause; i++) {
        textMenu[i].setFont(font);
        textMenu[i].setCharacterSize(fontSize);
        textMenu[i].setFillColor(sf::Color::White);
    }
    pauseMenu.setFont(font);
    pauseMenu.setCharacterSize(titleFontSize);
    pauseMenu.setString("Pause");
    pauseMenu.setFillColor(sf::Color::Yellow);
    pauseMenu.setPosition(
            sf::Vector2f(static_cast<float>(this->game->window.getSize().x) / 2 - pauseMenu.getGlobalBounds().width / 2,
                         buttonDistance * 2));

    //play
    textMenu[Resume].setFillColor(selectedColor);
    textMenu[Resume].setString("Resume");
    textMenu[Resume].setPosition(
            sf::Vector2f(
                    menuButton[Resume].getPosition().x + menuButton[Resume].getGlobalBounds().width / 2 -
                    textMenu[Resume].getGlobalBounds().width / 2,
                    menuButton[Resume].getPosition().y + menuButton[Resume].getGlobalBounds().height / 2 -
                    textMenu[Resume].getGlobalBounds().height / 2 + alignValue));

    //stats
    textMenu[Achievements].setString("Achievements");
    textMenu[Achievements].setPosition(
            sf::Vector2f(
                    menuButton[Achievements].getPosition().x + menuButton[Achievements].getGlobalBounds().width / 2 -
                    textMenu[Achievements].getGlobalBounds().width / 2,
                    menuButton[Achievements].getPosition().y + menuButton[Achievements].getGlobalBounds().height / 2 -
                    textMenu[Achievements].getGlobalBounds().height / 2 + alignValue));

    //exit
    textMenu[Exit].setString("Exit");
    textMenu[Exit].setPosition(
            sf::Vector2f(
                    menuButton[Exit].getPosition().x + menuButton[Exit].getGlobalBounds().width / 2 -
                    textMenu[Exit].getGlobalBounds().width / 2,
                    menuButton[Exit].getPosition().y + menuButton[Exit].getGlobalBounds().height / 2 -
                    textMenu[Exit].getGlobalBounds().height / 2 + alignValue));

    //if you add more buttons, you must updateNotCyclicalAnimation "nButtons" in the header file and unit testing
    nButtonSelected = Resume;
}

void PauseState::moveUp() {
    if (nButtonSelected - 1 >= -1) {
        textMenu[nButtonSelected].setFillColor(sf::Color::White);
        nButtonSelected--;
        if (nButtonSelected == -1)
            nButtonSelected = nButtonsPause - 1;
        textMenu[nButtonSelected].setFillColor(selectedColor);
    }
}

void PauseState::moveDown() {
    if (nButtonSelected + 1 <= nButtonsPause) {
        textMenu[nButtonSelected].setFillColor(sf::Color::White);
        nButtonSelected++;
        if (nButtonSelected == nButtonsPause)
            nButtonSelected = 0;
        textMenu[nButtonSelected].setFillColor(selectedColor);
    }
}

void PauseState::select() {
    switch (nButtonSelected) {
        case Resume:
            this->game->popState();
            break;
        case Achievements:
            this->game->pushState(new AchievementState(this->game));
            break;
        case Exit:
            AchievementManager::getInstance()->saveAchievements();
            this->game->window.close();
            break;
        default:
            std::cerr << "ERROR: SELECTED BUTTON NOT EXIST" << std::endl;
            break;
    }
}

