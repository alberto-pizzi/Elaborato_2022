//
// Created by alber on 22/12/2022.
//

#include "Dice.h"


int Dice::numRolls = 0;

Dice::Dice(int faces) : faces(faces) {
    srand(time(0));
}


int Dice::roll(int rolls) const {
    int result = 0;

    if ((numRolls % maxRolls) == 0)
        srand(time(0));

    for (int i = 0; i < rolls; i++)
        result += rand() % (faces + 1); //return numbers from 0 to faces (0 <= result <= faces)
    numRolls++;
    return result;
}

int Dice::getFaces() const {
    return faces;
}

void Dice::setFaces(int faces) {
    this->faces = faces;
}

