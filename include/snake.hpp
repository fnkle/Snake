#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Direction.hpp"
#include "vector.hpp"

#include <list>

class Snake
{
  public:
    std::list<vectorInt> snakePiecesPos;
    int snakePieceSize;

    Snake(vectorInt startPos);
    void move(enum Direction direction);
    void addSegment();
    bool checkInBounds(int width, int height);
    bool checkNoSnakeCollision();
    bool checkFruitSpawnCollision(vectorInt fruitPosition);
    bool canEatFruit(vectorInt fruitPosition);
};

#endif
