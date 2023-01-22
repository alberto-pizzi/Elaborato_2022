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
    //this->game->window.setView(this->view);
    this->game->window.setView(achievementView);
    this->game->window.clear(backgroundColor);
/*
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(32,32));
    shape.setPosition(achievementView.getCenter());
    shape.setFillColor(sf::Color::Red);
    this->game->window.draw(shape);
    */
    //this->game->window.draw(this->game->background);

    for (int i = 0; i < nButtons; i++)
        this->game->window.draw(mainMenu[i]);

    AchievementManager::drawAchievements(this->game->window);

}

void AchievementState::update(float dt) {
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
                //this->view.setSize(event.size.width, event.size.height);
                //this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->view));
                this->game->background.setScale(
                        float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
                        float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
                break;
            case sf::Event::KeyPressed:
                //Take input
                switch (event.key.code) {
                    case sf::Keyboard::Enter:
                        //select();
                        break;
                    case sf::Keyboard::W:
                        //moveUp();
                        achievementView.move(sf::Vector2f(0, scrollMove));
                        break;
                    case sf::Keyboard::S:
                        achievementView.move(sf::Vector2f(0, -scrollMove));
                        //moveDown();
                        break;
                    case sf::Keyboard::Escape:
                        this->game->popState();
                        break;
                }
                break;
        }
    }
}

AchievementState::AchievementState(Game *game) {
    this->game = game;
/*
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
    */

    std::string fontFile = "res/fonts/bloody.ttf";
    try {
        if (!font.loadFromFile(fontFile))
            throw GameException("Error opening numbersOrTitlesFont file", fontFile, false);
    } catch (GameException &e) {}
/*
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
    */
    //if you add more buttons, you must updateNotCyclicalAnimation "nButtons" in the header file and unit testing

    nButtonSelected = 0;



    //std::cout<<"Constructed"<<std::endl;



    //view
    achievementView.reset((sf::FloatRect(0, 0, viewSize.x, viewSize.y)));

    achievementView.setCenter(sf::Vector2f(
            AchievementManager::getInstance()->achievements.begin()->second->getBoxSprite().getPosition().x +
            AchievementManager::getInstance()->achievements.begin()->second->getBoxSprite().getGlobalBounds().width / 2,
            AchievementManager::getInstance()->achievements.begin()->second->getBoxSprite().getPosition().y +
            AchievementManager::getInstance()->achievements.begin()->second->getBoxSprite().getGlobalBounds().height /
            2));
    this->game->window.setView(achievementView);

}

void AchievementState::moveUp() {
    /*
    if (nButtonSelected - 1 >= -1) {
        //mainMenu[nButtonSelected].setFillColor(sf::Color::White);
        nButtonSelected--;
        std::prev(localIt);
        if (nButtonSelected == -1) {
            nButtonSelected = nButtons - 1;
            localIt = AchievementManager::getInstance()->achievements.end();
        }
        //mainMenu[nButtonSelected].setFillColor(sf::Color(102, 0, 0));
        achievementView.setCenter(sf::Vector2f (localIt->second->getBoxSprite().getPosition().x + localIt->second->getBoxSprite().getGlobalBounds().width/2,
                                                localIt->second->getBoxSprite().getPosition().y + localIt->second->getBoxSprite().getGlobalBounds().height/2));

    }
     */
}

void AchievementState::moveDown() {
    /*
    if (nButtonSelected + 1 <= nButtons) {
        //mainMenu[nButtonSelected].setFillColor(sf::Color::White);
        nButtonSelected++;
        std::next(localIt);
        if (nButtonSelected == nButtons) {
            nButtonSelected = 0;
            localIt = AchievementManager::getInstance()->achievements.begin();
        }
        //mainMenu[nButtonSelected].setFillColor(sf::Color(102, 0, 0));
        achievementView.setCenter(sf::Vector2f (localIt->second->getBoxSprite().getPosition().x + localIt->second->getBoxSprite().getGlobalBounds().width/2,
                                                localIt->second->getBoxSprite().getPosition().y + localIt->second->getBoxSprite().getGlobalBounds().height/2));
    }
     */
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