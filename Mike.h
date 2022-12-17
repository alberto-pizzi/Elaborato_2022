//
// Created by alber on 12/11/2022.
//

#ifndef ELABORATO_MIKE_H
#define ELABORATO_MIKE_H

#include "GameCharacter.h"
#include "GameException.h"
#include "Gui.h"

enum Directions {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
};
enum typeOfWeapon {
    HANDGUN = 0, ASSAULT_RIFLE, SHOTGUN,
};

class Mike : public GameCharacter {
private:
    int killStreak;
public:
    explicit Mike(const sf::Texture &mikeTexture, const sf::Texture &handgunTexture, const sf::Vector2i &spawnTile,
                  const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, bool animated = true, int hp = 20,
                  float speed = 250.f, unsigned int points = 0, unsigned int coins = 0, int armor = 0,
                  bool bubble = false,
                  int streak = 0);

    virtual ~Mike();

    Gui gui;

    void move(const sf::Vector2f &offset, float dt) override;

    bool isKillStreak(GameCharacter &character);

    void drawEntity(sf::RenderWindow &window) override;

    void directionInput(const sf::Vector2f &viewfinderPos, bool (&skinDirection)[4]);

    void setWeaponPosToShouldersPos();
};


#endif //ELABORATO_MIKE_H
