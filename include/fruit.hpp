#ifndef FRUIT_HPP
#define FRUIT_HPP
#include "vector.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <ctime>
#include <stdlib.h>

class Fruit
{
  public:
    vectorInt fruitPosition;
    int fruitSize;
    SDL_Rect fruitRect;
    Fruit(int tileSize, vectorInt position);
    void render(SDL_Renderer **renderer);
};
#endif