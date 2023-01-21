//
// Created by alber on 21/01/2023.
//

#ifndef ELABORATO_OBSERVER_H
#define ELABORATO_OBSERVER_H


#include <iostream>
#include <string>

class Observer {
protected:
    virtual ~Observer() = default;

public:
    virtual void update(std::string achievementName, unsigned int value) = 0;
};


#endif //ELABORATO_OBSERVER_H
