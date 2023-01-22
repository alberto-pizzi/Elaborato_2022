//
// Created by alber on 21/01/2023.
//

#ifndef ELABORATO_SUBJECT_H
#define ELABORATO_SUBJECT_H


#include <iostream>
#include "Observer.h"

class Subject {
public:
    virtual void registerObserver(Observer *observer) = 0;

    virtual void removeObserver(Observer *observer) = 0;

    virtual void notifyObserver(std::string achievementName, unsigned int value) const = 0;

    virtual ~Subject() = default;
};


#endif //ELABORATO_SUBJECT_H
