#include "Direction.hpp"
#include "collisions.hpp"
#include "vector.hpp"
#include <SDL2/SDL.h>
#include <list>

class Snake
{
  public:
    std::list<vectorInt> snakePiecesPos;
    int snakePieceSize;

    Snake(int snakePieceSize);
    void move(enum Direction direction);
    void addSegment();
    bool checkInBounds(int width, int height);
    bool checkNoSnakeCollision();
};