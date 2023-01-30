//
// Created by alber on 22/01/2023.
//

#include "AchievementState.h"

void AchievementState::draw(float dt) const {
    this->game->window.setView(achievementView);
    this->game->window.clear(backgroundColor);

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
                    case sf::Keyboard::W:
                        achievementView.move(sf::Vector2f(0, -scrollMove));
                        break;
                    case sf::Keyboard::S:
                        achievementView.move(sf::Vector2f(0, scrollMove));
                        break;
                    case sf::Keyboard::Escape:
                        this->game->popState();
                        break;
                }
                break;
        }

        //mouse scrolling
        float delta = event.mouseWheelScroll.delta;
        if (delta != 0)
            achievementView.move(sf::Vector2f(0, -delta * scrollMove));
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
                achievements.begin()->second->getAchievements().begin()->get()->getBoxSprite().getPosition().x +
                achievements.begin()->second->getAchievements().begin()->get()->getBoxSprite().getGlobalBounds().width /
                2,
                achievements.begin()->second->getAchievements().begin()->get()->getBoxSprite().getPosition().y +
                achievements.begin()->second->getAchievements().begin()->get()->getBoxSprite().getGlobalBounds().height /
                2));
    } else
        achievementView.setCenter(sf::Vector2f(
                AchievementManager::getInstance()->achievements.begin()->second->getAchievements().begin()->get()->getBoxSprite().getPosition().x +
                AchievementManager::getInstance()->achievements.begin()->second->getAchievements().begin()->get()->getBoxSprite().getGlobalBounds().width /
                2,
                AchievementManager::getInstance()->achievements.begin()->second->getAchievements().begin()->get()->getBoxSprite().getPosition().y +
                AchievementManager::getInstance()->achievements.begin()->second->getAchievements().begin()->get()->getBoxSprite().getGlobalBounds().height /
                2));

    this->game->window.setView(achievementView);
}

void AchievementState::loadAchievements() {
    std::ifstream achievementFile;
    bool firstTime = true;


    achievementFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        achievementFile.open(achievementFileName);
    }
    catch (std::ios_base::failure &e) {
        throw GameException("Error opening achievement file", achievementFileName, false);
    }

    int totalAchievements, achievementTypeInt;
    std::string achievementName, actualProgress, target, totalAchievementsString, achievementType, previousAchievementType;

    //read total achievements
    std::getline(achievementFile, totalAchievementsString);
    totalAchievements = std::stoi(totalAchievementsString);

    //init map
    achievements.clear();

    //read each achievement
    for (int i = 0; i < totalAchievements; i++) {
        std::getline(achievementFile, achievementType);
        if (firstTime)
            previousAchievementType = achievementType;
        std::getline(achievementFile, achievementName);
        std::getline(achievementFile, actualProgress);
        std::getline(achievementFile, target);
        achievementTypeInt = std::stoi(achievementType);

        if ((achievementType != previousAchievementType) || firstTime) {
            achievements[achievementTypeInt] = std::unique_ptr<AchievementType>(
                    new AchievementType(achievementsTextures.getTextureRef("box"),
                                        achievementsTextures.getTextureRef("trophy"),
                                        achievementName, std::stoul(target), progressFont, achievementTypeInt));
            firstTime = false;
        } else
            achievements[achievementTypeInt]->createAchievement(achievementName, std::stoul(target));
        achievements[achievementTypeInt]->update(std::stoul(actualProgress));
        previousAchievementType = achievementType;
    }

    achievementFile.close();
}

void AchievementState::drawAchievementsFromFile() const {
    for (auto it = achievements.begin();
         it != achievements.end(); it++) {
        it->second->drawAchievements(this->game->window);
    }
}

void AchievementState::loadTextures() {
    achievementsTextures.loadTexture("box", "res/textures/message_box.png");
    achievementsTextures.loadTexture("trophy", "res/textures/trophy.png");
}
