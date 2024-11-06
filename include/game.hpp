#ifndef GAME_HPP
#define GAME_HPP

#include "fruit.hpp"
#include "Renderer.hpp"
#include "snake.hpp"

#include <list>

class Game
{
  private:
    Snake snake;
	Renderer renderer;
    int numTilesX;
    int numTilesY;
    int numFruits;
    bool gameLoop;
    enum Direction snakeDirection;
    std::list<Fruit> listFruits;

  public:
    Game(Renderer renderer, int numTilesX, int numTilesY);
    void update();
    void fillFruits();
    void handleEvents();
    void loop();
};
#endif
