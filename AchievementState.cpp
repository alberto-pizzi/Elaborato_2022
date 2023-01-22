//
// Created by alber on 22/01/2023.
//

#include "AchievementState.h"

enum NameButton {
    //these numbers are related with nButtons
    Back = 0,
    Stats = 1,
    Exit = 2,
};

void AchievementState::draw(float dt) const {
    this->game->window.setView(this->view);
    this->game->window.clear(sf::Color::Blue);
    //this->game->window.draw(this->game->background);

    for (int i = 0; i < nButtons; i++)
        this->game->window.draw(mainMenu[i]);

}

void AchievementState::update(float dt) {
    /*
    if (!printed) {
        for (auto it = achievementManager->achievements.begin(); it != achievementManager->achievements.end(); it++)
            std::cout << "KEY: " << it->first << " VALUE: " << it->second->getActualProgress() << std::endl;
        std::cout<<"FINISH"<<std::endl;
        printed = true;
    }
     */
}

void AchievementState::handleInput() {
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
                    case sf::Keyboard::Escape:
                        this->game->popState();
                        break;
                }
                break;
            }
        }
    }
}

AchievementState::AchievementState(Game *game) {
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
    mainMenu[Back].setFont(font);
    mainMenu[Back].setFillColor(sf::Color(102, 0, 0));
    mainMenu[Back].setString("Back");
    mainMenu[Back].setCharacterSize(fontSize);
    mainMenu[Back].setPosition(
            sf::Vector2f(static_cast<float>(this->game->window.getSize().x) / 2 - static_cast<float>(fontSize),
                         static_cast<float>(this->game->window.getSize().y) / 2 - static_cast<float>(fontSize)));

    //stats
    mainMenu[Stats].setFont(font);
    mainMenu[Stats].setFillColor(sf::Color::White);
    mainMenu[Stats].setString("Stats");
    mainMenu[Stats].setCharacterSize(50);
    mainMenu[Stats].setPosition(
            sf::Vector2f(static_cast<float>(this->game->window.getSize().x) / 2 - static_cast<float>(fontSize),
                         (static_cast<float>(this->game->window.getSize().y) / 2 - static_cast<float>(fontSize)) *
                         1.5));

    //exit
    mainMenu[Exit].setFont(font);
    mainMenu[Exit].setFillColor(sf::Color::White);
    mainMenu[Exit].setString("Exit");
    mainMenu[Exit].setCharacterSize(50);
    mainMenu[Exit].setPosition(sf::Vector2f(static_cast<float>(this->game->window.getSize().x) / 2 - 50,
                                            (static_cast<float>(this->game->window.getSize().y) / 2 -
                                             static_cast<float>(fontSize)) * 2));
    //if you add more buttons, you must updateNotCyclicalAnimation "nButtons" in the header file and unit testing

    nButtonSelected = Back;


}

void AchievementState::moveUp() {
    if (nButtonSelected - 1 >= -1) {
        mainMenu[nButtonSelected].setFillColor(sf::Color::White);
        nButtonSelected--;
        if (nButtonSelected == -1)
            nButtonSelected = nButtons - 1;
        mainMenu[nButtonSelected].setFillColor(sf::Color(102, 0, 0));
    }
}

void AchievementState::moveDown() {
    if (nButtonSelected + 1 <= nButtons) {
        mainMenu[nButtonSelected].setFillColor(sf::Color::White);
        nButtonSelected++;
        if (nButtonSelected == nButtons)
            nButtonSelected = 0;
        mainMenu[nButtonSelected].setFillColor(sf::Color(102, 0, 0));
    }
}

void AchievementState::select() {
    switch (nButtonSelected) {
        case Back:
            //this->loadPlay();
            this->game->popState();
            break;
        case Stats:
            //std::cout << "i'm stats" << std::endl;
            break;
        case Exit:
            this->game->window.close();
            break;
        default:
            std::cerr << "ERROR: SELECTED BUTTON NOT EXIST" << std::endl;
            break;
    }
}