
#include "vector.hpp"
#include <ctime>
#include <stdlib.h>

class Fruit
{
  public:
    vectorInt fruitPosition;
    int fruitSize;

    Fruit(int tileSize, vectorInt position);
};