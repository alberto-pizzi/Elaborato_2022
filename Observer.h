//
// Created by alber on 21/01/2023.
//

#ifndef ELABORATO_OBSERVER_H
#define ELABORATO_OBSERVER_H


#include <iostream>
#include <string>

class Observer {
public:
    virtual void update(std::string achievementName, unsigned int value) = 0;

    virtual ~Observer() = default;
};


#endif //ELABORATO_OBSERVER_H
