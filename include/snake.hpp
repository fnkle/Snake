#include "Direction.hpp"
#include "vector.hpp"
#include <SDL2/SDL.h>
#include <SDL_render.h>
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
    bool checkFruitSpawnCollision(vectorInt fruitPosition);
    bool canEatFruit(vectorInt fruitPosition);
    void render(SDL_Renderer **renderer);
};