//
// Created by Samuel Kodytek on 26/06/2018.
//

#include "Coordinate.h"

Coordinate::Coordinate(int x, int y) {
    this->x = x;
    this->y = y;
}

int Coordinate::getX() {
    return x;
}

int Coordinate::getY() {
    return y;
}
