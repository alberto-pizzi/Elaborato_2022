//
// Created by alber on 09/01/2023.
//

#include "Node.h"

Node::Node(int x, int y, bool walkable) : column(x), row(y), walkable(walkable), gCost(0), hCost(0), fCost(0),
                                          parent(nullptr) {

}