//
// Created by alber on 12/11/2022.
//

#ifndef ELABORATO_BONUS_H
#define ELABORATO_BONUS_H

#include "GameCharacter.h"
#include "GameException.h"
#include <memory>
#include "Dice.h"

enum BonusType {
    NEW_WEAPON = 0, AMMUNITION, COINS, INCREASED_DAMAGE, LIFE_POINTS, PROTECTION_BUBBLE, NUKE,
};

class Bonus {
private:
    int bonusType;
protected:
    int bonusPoints;
    sf::Time stayTime;
    sf::Clock stayTimer;
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<sf::IntRect> animationFrames;


public:
    bool isActiveAnimation = false;
    bool isEndedAnimation = false;
    bool despawnStarted = false;
    bool isInfiniteAnimation = false;

    Animation currentAnimation{animationFrames, 10.f};

    Bonus(const sf::Texture &texture, int points, sf::Time stayTime, sf::Vector2f spawnCoords,
          std::vector<sf::IntRect> animationFrames, int bonusType, bool isInfinite);

    virtual void doSpecialAction(GameCharacter &character) = 0;

    void addPoints(GameCharacter &target) const;

    bool isAbove(const GameCharacter &character) const;

    void drawBonus(sf::RenderWindow &window);

    virtual void
    startDespawining(); //WARNING: call this when you want despawning a new weapon (for startDespawining animation)

    int getBonusType() const;

    const sf::Time &getStayTime() const;

    const sf::Clock &getStayTimer() const;


};


#endif //ELABORATO_BONUS_H
