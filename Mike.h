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
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Animation currentAnimation{idle, 10.0f};

    explicit Mike(int hp = 20, int speed = 1, int points = 0, int coins = 0, int armor = 0, bool bubble = false,
                  int streak = 0); //FIXME change speed and check hp
    void move(const sf::Vector2f &offset, float dt) override;

    bool isKillStreak(GameCharacter &character);

    void drawEntity(sf::RenderWindow &window) override;

};


#endif //ELABORATO_MIKE_H
