//
// Created by alber on 12/11/2022.
//

#ifndef ELABORATO_MIKE_H
#define ELABORATO_MIKE_H

#include "GameCharacter.h"
#include "Gui.h"
#include "Subject.h"
#include <list>
#include "AchievementManager.h"

enum typeOfWeapon {
    HANDGUN = 0, ASSAULT_RIFLE, SHOTGUN,
};

class Mike : public GameCharacter, public Subject {
private:
    bool bubble;
    int killStreak = 0;
    struct ActualBonus {
        int bonusType;
        sf::Clock effectTimer;
        sf::Time effectTime;
    };

    //kills
    unsigned int kills = 0;
    unsigned int roundKills = 0;
    std::map<int, unsigned int> enemyTypeKills;

    //bonuses
    std::map<int, unsigned int> bonusTypeCollected;
    unsigned int bonusesCollected = 0;
    std::vector<ActualBonus> actualBonuses;

    //observers
    std::list<Observer *> observers;

    //WARNING: Mike achievements are saved in AchievementManager (it is a singleton class, so it has just one instance)
public:
    Gui gui;


    Mike(const sf::Texture &mikeTexture, const sf::Texture &handgunTexture, const sf::Texture &handgunBulletTexture,
         const sf::Vector2i &spawnTile, const TextureManager &guiTexManager, const sf::Vector2i &tileSize,
         const sf::Vector2i &rectSkin, float startRoundCountdownSeconds, float hp = 20, float speed = 220.f,
         float armor = 0);

    virtual ~Mike();

    bool isKillStreak(GameCharacter &character);

    //void drawEntity(sf::RenderWindow &window);
    void drawEntity(sf::RenderWindow &window, bool gameOver) override;

    void updateCharacterColor() override;

    void receiveDamage(float damagePoints) override;

    void addToOwnBonuses(int bonusType, sf::Time duration);

    void updateActiveBonuses();

    std::vector<ActualBonus> getActualBonuses() const;

    unsigned int getKills() const;

    void resetRoundKills();

    unsigned int getRoundKills() const;

    void registerObserver(Observer *observer) override;

    void removeObserver(Observer *observer) override;

    void notifyObserver(std::string achievementName, unsigned int value) const override;

    void incrementKills(int enemyType);

    bool isBubble() const;

    void setBubble(bool bubble);

    void incrementBonusCollected(int bonusType);
};


#endif //ELABORATO_MIKE_H
