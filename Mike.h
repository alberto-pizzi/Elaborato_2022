//
// Created by alber on 12/11/2022.
//

#ifndef ELABORATO_MIKE_H
#define ELABORATO_MIKE_H

#include "GameCharacter.h"
#include "GameException.h"

enum Directions {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
};

class Mike : public GameCharacter {
private:
    int killStreak;


public:


    explicit Mike(const sf::Texture &mikeTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
                  const sf::Vector2i &rectSkin, bool animated = true, int hp = 20, float speed = 250.f, int points = 0,
                  int coins = 0, int armor = 0, bool bubble = false, int streak = 0);

    virtual ~Mike();

    void move(const sf::Vector2f &offset, float dt) override;

    bool isKillStreak(GameCharacter &character);

    void drawEntity(sf::RenderWindow &window) override;

    void directionInput(const sf::Vector2f &viewfinderPos);

};


#endif //ELABORATO_MIKE_H
