
#include "vector.hpp"
#include <stdlib.h>
#include <ctime>


class Fruit{
public:
    vectorInt fruitPosition;
    int fruitSize;

    Fruit(int tileSize, vectorInt position){

        this-> fruitPosition = position;
        this->fruitSize = tileSize;
    }
};