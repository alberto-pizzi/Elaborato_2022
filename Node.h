//
// Created by alber on 09/01/2023.
//

#ifndef ELABORATO_NODE_H
#define ELABORATO_NODE_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <algorithm>
#include <vector>
#include <memory>

class Node {
private:
    friend class AI;

    int gCost;
    int fCost;
    int hCost;
    std::shared_ptr<Node> parent;
    bool walkable;
    int column;
    int row;

public:
    Node(int x, int y, bool walkable);

};


#endif //ELABORATO_NODE_H
