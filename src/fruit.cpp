#include "fruit.hpp"

Fruit::Fruit(int tileSize, vectorInt position)
{
    this->fruitPosition = position;
    this->fruitSize = tileSize;
    fruitRect.x = fruitPosition.x;
    fruitRect.y = fruitPosition.y;
    fruitRect.w = fruitSize;
    fruitRect.h = fruitSize;
}

void Fruit::render(SDL_Renderer **renderer)
{
    SDL_SetRenderDrawColor(*renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(*renderer, &fruitRect);
}