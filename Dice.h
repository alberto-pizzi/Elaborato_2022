//
// Created by alber on 22/12/2022.
//

#ifndef ELABORATO_DICE_H
#define ELABORATO_DICE_H

#include <ctime>
#include <cstdlib>

class Dice {
public:
    explicit Dice(int faces = 6);

    int roll(int rolls) const;

    int getFaces() const;

private:
    int faces;
    static int numRolls;
    const int maxRolls = 1000; // max number of rolls, when numRolls > maxRolls reinit RNG seed

};


#endif //ELABORATO_DICE_H