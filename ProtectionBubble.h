//
// Created by alber on 29/12/2022.
//

#ifndef ELABORATO_PROTECTIONBUBBLE_H
#define ELABORATO_PROTECTIONBUBBLE_H

#include "Bonus.h"

class ProtectionBubble : public Bonus {
public:
    ProtectionBubble(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points = 10,
                     sf::Time stayTime = sf::seconds(25));

    void doSpecialAction(Mike &character) override;
};


#endif //ELABORATO_PROTECTIONBUBBLE_H
