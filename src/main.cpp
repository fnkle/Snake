#include <iostream>
#include <SDL2/SDL.h>
#include "snake.hpp"
#include "fruit.hpp"
#include "collisions.hpp"

using namespace std;

int initSDL(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
{
    // Initialise SDL2 so we can use functions
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
        return -4;
    }
    else
    {
        // Create window
        *window = SDL_CreateWindow("Simulations", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            cout << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
            return -1;
        }

        *renderer = SDL_CreateRenderer(*window, -1, 0);
        if (renderer == NULL)
        {
            cout << "Renderer could not be created! SDL_Error: %s\n", SDL_GetError();
            return -2;
        }

        return 1;
    }
}

int main()
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    int width = 800;
    int height = 800;
    int tileSize = 40;
    int numTilesX = width / tileSize;
    int numTilesY = width / tileSize;

    int init = initSDL(&window, &renderer, width, height);
    int numFruit = 15;
    list<Fruit> fruits = {};
    srand((unsigned)time(NULL));

    for (int i = 0; i < numFruit; i++)
    {
        int fruitXPosition = rand() % numTilesX;
        int fruitYPosition = rand() % numTilesY;

        fruits.push_back(Fruit(tileSize, vectorInt(fruitXPosition * tileSize, fruitYPosition * tileSize)));
    }

    bool loop = true;

    Snake snake = Snake(tileSize);

    enum Direction direction = LEFT;

    bool updatedDirection;

    if (init)
    {
        while (loop)
        {
            updatedDirection = false;
            SDL_RenderPresent(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderClear(renderer);

            // Get next event
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    loop = false;
                    break;
                }
                else if (event.type = SDL_KEYDOWN && !updatedDirection)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        if (direction != DOWN)
                        {
                            direction = UP;
                            updatedDirection = true;
                        }
                        break;
                    case SDLK_DOWN:
                        if (direction != UP)
                        {
                            direction = DOWN;
                            updatedDirection = true;
                        }
                        break;
                    case SDLK_LEFT:
                        if (direction != RIGHT)
                        {
                            direction = LEFT;
                            updatedDirection = true;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (direction != LEFT)
                        {
                            direction = RIGHT;
                            updatedDirection = true;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }

            snake.move(direction);

            if(!snake.checkInBounds(width, height)){
                loop = false;
            }

            if(!snake.checkNoSnakeCollision()){
                loop = false;
            }

            for (vectorInt snakePiece : snake.snakePiecesPos)
            {
                SDL_Rect snakePieceRect = SDL_Rect();
                snakePieceRect.x = snakePiece.x;
                snakePieceRect.y = snakePiece.y;
                snakePieceRect.w = snake.snakePieceSize;
                snakePieceRect.h = snake.snakePieceSize;

                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(renderer, &snakePieceRect);
            }

            for (Fruit fruit : fruits)
            {
                SDL_Rect fruitRect = SDL_Rect();

                fruitRect.x = fruit.fruitPosition.x;
                fruitRect.y = fruit.fruitPosition.y;
                fruitRect.w = fruit.fruitSize;
                fruitRect.h = fruit.fruitSize;

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &fruitRect);
            }

            list<Fruit>::iterator fruitItr;
            for (fruitItr = fruits.begin(); fruitItr != fruits.end(); fruitItr++)
            {

                Fruit fruit = *fruitItr;

                if (squareOnSquareCollision(fruit.fruitPosition, snake.snakePiecesPos.front()))
                {
                    fruits.erase(fruitItr);
                    snake.addSegment();
                    int fruitXPosition = rand() % numTilesX;
                    int fruitYPosition = rand() % numTilesY;

                    fruits.push_back(Fruit(tileSize, vectorInt(fruitXPosition * tileSize, fruitYPosition * tileSize)));
                    break;
                }
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(150);
        }
    }
}
