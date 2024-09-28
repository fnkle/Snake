#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "vector.hpp"

bool squareOnSquareCollision(vectorInt squareOnePosition, vectorInt squareTwoPosition){
    if (squareOnePosition.x == squareTwoPosition.x){
        if (squareOnePosition.y == squareTwoPosition.y){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

#endif