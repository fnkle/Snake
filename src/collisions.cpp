#include "collisions.hpp"

bool tileCollision(vectorInt squareOnePosition, vectorInt squareTwoPosition){
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
