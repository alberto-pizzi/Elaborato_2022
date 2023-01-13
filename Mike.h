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
    enum BonusType {
        NEW_WEAPON = 0, AMMUNITION, COINS, INCREASED_DAMAGE, LIFE_POINTS, PROTECTION_BUBBLE, NUKE,
    };
    int killStreak;
    struct ActualBonus {
        int bonusType;
        sf::Clock effectTimer;
        sf::Time effectTime;
    };
    std::vector<ActualBonus> actualBonuses;
public:
    Gui gui;

    Mike(const sf::Texture &mikeTexture, const sf::Texture &handgunTexture, const sf::Texture &handgunBulletTexture,
         const sf::Vector2i &spawnTile, const TextureManager &guiTexManager, const sf::Vector2i &tileSize,
         const sf::Vector2i &rectSkin, float startRoundCountdownSeconds, bool animated = true, int hp = 20,
         float speed = 220.f, unsigned int points = 0, unsigned int coins = 0, int armor = 0, bool bubble = false,
         int streak = 0);

    virtual ~Mike();



    bool isKillStreak(GameCharacter &character);

    //void drawEntity(sf::RenderWindow &window);
    void drawEntity(sf::RenderWindow &window, bool gameOver) override;

    void addToOwnBonuses(int bonusType, sf::Time duration);

    void updateActiveBonuses();


    std::vector<ActualBonus> getActualBonuses() const;
};


#endif //ELABORATO_MIKE_H
