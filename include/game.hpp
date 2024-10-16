#include <SDL_render.h>
#ifndef GAME_HPP
#include "fruit.hpp"
#include "snake.hpp"
#include <list>

class Game
{
  private:
    Snake snake;
    SDL_Renderer *renderer;
    int width;
    int height;
    int tileSize;
    int numTilesX;
    int numTilesY;
    int numFruits;
    bool gameLoop;
    enum Direction snakeDirection;
    std::list<Fruit> listFruits;

  public:
    Game(SDL_Renderer **renderer, int width, int height);
    void update();
    void fillFruits();
    void handleEvents();
    void loop();
};
#endif