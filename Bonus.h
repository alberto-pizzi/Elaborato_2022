//
// Created by alber on 12/11/2022.
//

#ifndef ELABORATO_BONUS_H
#define ELABORATO_BONUS_H


class Bonus {
protected:
    int bonusPoints;
public:
    virtual void doSpecialAction() = 0;

    void addPoints();

};


#endif //ELABORATO_BONUS_H
