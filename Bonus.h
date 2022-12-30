//
// Created by alber on 12/11/2022.
//

#ifndef ELABORATO_BONUS_H
#define ELABORATO_BONUS_H

#include "GameCharacter.h"
#include "GameException.h"
#include <memory>
#include "Dice.h"
#include "Mike.h"


enum BonusType {
    NEW_WEAPON = 0, AMMUNITION, COINS, INCREASED_DAMAGE, LIFE_POINTS, PROTECTION_BUBBLE, NUKE, ARMOR
};

enum totFramesBonusBox {
    IDLE = 1, SPAWN = 7, DESPAWN = 7,
};

class Bonus {
private:
    int bonusType;
    bool hasDespawnAnimation;
protected:
    int bonusPoints;
    sf::Time stayTime;
    sf::Time duration = sf::seconds(0); //default value
    bool isOwnable;
    sf::Clock stayTimer;
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<sf::IntRect> animationFrames;

    //animation
    sf::Vector2i bonusFrameSize;
    sf::Vector2f translation;
    std::vector<sf::IntRect> idleBonusBox;
    std::vector<sf::IntRect> despawnFrames;
    const sf::Vector2i animationFrameSize = {64, 64};
public:
    bool isActiveAnimation = false;
    bool isEndedAnimation = false;
    bool despawnStarted = false;
    bool isInfiniteAnimation = false;

    Animation currentAnimation{animationFrames, 10.f};

    Bonus(const sf::Texture &texture, int points, sf::Time stayTime, sf::Vector2f spawnCoords,
          const std::vector<sf::IntRect> &animationFrames, int bonusType, sf::Vector2i frameSize,
          int textureRowIndex, bool isInfinite, bool ownable, bool hasDespawnAnimation);

    virtual void doSpecialAction(Mike &character) = 0;

    void addPoints(GameCharacter &target) const;

    bool isAbove(const sf::FloatRect &characterGlobalPos) const;

    void drawBonus(sf::RenderWindow &window);

    virtual void
    startDespawining(); //WARNING: call this when you want despawning a new weapon (for startDespawining animation)

    int getBonusType() const;

    const sf::Time &getStayTime() const;

    const sf::Clock &getStayTimer() const;

    const sf::Time &getDuration() const;


};


#endif //ELABORATO_BONUS_H
