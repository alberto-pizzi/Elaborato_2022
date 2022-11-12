//
// Created by alber on 12/11/2022.
//

#ifndef ELABORATO_MIKE_H
#define ELABORATO_MIKE_H

#include "GameCharacter.h"

class Mike : public GameCharacter {
private:
    int killStreak;
public:
    explicit Mike(int hp = 20, int speed = 1, int points = 0, int coins = 0, int armor = 0, bool bubble = false,
                  int streak = 0); //FIXME change speed and check hp
    void move(sf::Vector2f pos) override;

    bool isKillStreak(GameCharacter &character);

};


#endif //ELABORATO_MIKE_H
