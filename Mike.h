//
// Created by alber on 12/11/2022.
//

#ifndef ELABORATO_MIKE_H
#define ELABORATO_MIKE_H

#include "GameCharacter.h"
#include "Gui.h"

enum typeOfWeapon {
    HANDGUN = 0, ASSAULT_RIFLE, SHOTGUN,
};

class Mike : public GameCharacter {
private:
    int killStreak = 0;
    struct ActualBonus {
        int bonusType;
        sf::Clock effectTimer;
        sf::Time effectTime;
    };
    std::vector<ActualBonus> actualBonuses;
    unsigned int kills = 0;
    unsigned int roundKills = 0;
public:
    Gui gui;

    Mike(const sf::Texture &mikeTexture, const sf::Texture &handgunTexture, const sf::Texture &handgunBulletTexture,
         const sf::Vector2i &spawnTile, const TextureManager &guiTexManager, const sf::Vector2i &tileSize,
         const sf::Vector2i &rectSkin, float startRoundCountdownSeconds, float hp = 20, float speed = 220.f,
         int armor = 0);

    virtual ~Mike();

    bool isKillStreak(GameCharacter &character);

    //void drawEntity(sf::RenderWindow &window);
    void drawEntity(sf::RenderWindow &window, bool gameOver) override;

    void addToOwnBonuses(int bonusType, sf::Time duration);

    void updateActiveBonuses();

    std::vector<ActualBonus> getActualBonuses() const;

    unsigned int getKills() const;

    void setKills(unsigned int kills);

    unsigned int getRoundKills() const;

    void setRoundKills(unsigned int roundKills);
};


#endif //ELABORATO_MIKE_H
