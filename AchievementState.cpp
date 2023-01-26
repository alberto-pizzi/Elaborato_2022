//
// Created by alber on 22/01/2023.
//

#include "AchievementState.h"

void AchievementState::draw(float dt) const {
    this->game->window.setView(achievementView);
    this->game->window.clear(backgroundColor);

    //FIXME remove it
    /*
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(32, 32));
    sf::Vector2i shapePos = {0, 50};
    sf::Vector2f worldShapePos = this->game->window.mapPixelToCoords(shapePos);
    shape.setPosition(worldShapePos);
    shape.setFillColor(sf::Color::Red);
    this->game->window.draw(shape);
     */

    //this->game->window.draw(this->game->background);
    if (AchievementManager::getInstance())
        AchievementManager::drawAchievements(this->game->window);
    else
        drawAchievementsFromFile();

}

void AchievementState::update(float dt) {
    //std::cout<<"Y view: "<<achievementView.getCenter().y<<std::endl;
}

void AchievementState::handleInput() {
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


    std::string fontFile = "res/fonts/bloody.ttf";
    try {
        if (!font.loadFromFile(fontFile))
            throw GameException("Error opening numbersOrTitlesFont file", fontFile, false);
    } catch (GameException &e) {}

    //view
    achievementView.reset((sf::FloatRect(0, 0, viewSize.x, viewSize.y)));

    //load font
    std::string textFontFile = "res/fonts/arial.ttf";
    try {
        if (!progressFont.loadFromFile(textFontFile))
            throw GameException("Error opening textFontFile file", textFontFile, false);
    } catch (GameException &e) {
        exit(1); //close all
    }

    if (!AchievementManager::getInstance()) {
        loadTextures();
        loadAchievements();
        achievementView.setCenter(sf::Vector2f(
                achievements.begin()->second->getBoxSprite().getPosition().x +
                achievements.begin()->second->getBoxSprite().getGlobalBounds().width / 2,
                achievements.begin()->second->getBoxSprite().getPosition().y +
                achievements.begin()->second->getBoxSprite().getGlobalBounds().height /
                2));
    } else
        achievementView.setCenter(sf::Vector2f(
                AchievementManager::getInstance()->achievements.begin()->second->getBoxSprite().getPosition().x +
                AchievementManager::getInstance()->achievements.begin()->second->getBoxSprite().getGlobalBounds().width /
                2,
                AchievementManager::getInstance()->achievements.begin()->second->getBoxSprite().getPosition().y +
                AchievementManager::getInstance()->achievements.begin()->second->getBoxSprite().getGlobalBounds().height /
                2));

    //FIXME remove it
    //achievementView.setCenter(sf::Vector2f(-5*32,-5*32));
    /*
    std::cout << "X: "
              << AchievementManager::getInstance()->achievements.begin()->second->getBoxSprite().getPosition().x <<
              " Y: " << AchievementManager::getInstance()->achievements.begin()->second->getBoxSprite().getPosition().y
              << std::endl;
              */
    this->game->window.setView(achievementView);

    //init Y box pos as half window size
    Achievement::setPreviousBoxPosY(static_cast<float>(this->game->window.getSize().y) / 2.f);
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

void AchievementState::loadAchievements() {
    std::ifstream achievementFile;

    achievementFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        achievementFile.open(achievementFileName);
    }
    catch (std::ios_base::failure &e) {
        throw GameException("Error opening achievement file", achievementFileName, false);
    }

    int totalAchievements;
    std::string achievementName, actualProgress, target, totalAchievementsString;

    //read total achievements
    std::getline(achievementFile, totalAchievementsString);
    totalAchievements = std::stoi(totalAchievementsString);

    //init map
    achievements.clear();

    //read each achievement
    for (int i = 0; i < totalAchievements; i++) {
        std::getline(achievementFile, achievementName);
        std::getline(achievementFile, actualProgress);
        std::getline(achievementFile, target);
        achievements[achievementName] = std::unique_ptr<Achievement>(
                new Achievement(achievementsTextures.getTextureRef("box"), achievementsTextures.getTextureRef("trophy"),
                                achievementName, std::stoul(target), progressFont));
        achievements[achievementName]->update(std::stoul(actualProgress));
    }

    achievementFile.close();
}

void AchievementState::drawAchievementsFromFile() const {
    for (auto it = achievements.begin();
         it != achievements.end(); it++) {
        it->second->drawAchievement(this->game->window);
    }
}

void AchievementState::loadTextures() {
    achievementsTextures.loadTexture("box", "res/textures/message_box.png");
    achievementsTextures.loadTexture("trophy", "res/textures/trophy.png");
}
