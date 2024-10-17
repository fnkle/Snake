#include "game.hpp"
#include "fruit.hpp"
#include "vector.hpp"
#include <SDL_render.h>

Game::Game(SDL_Renderer **renderer, int width, int height) : snake(Snake(0))
{
    this->width = width;
    this->height = height;
    tileSize = 40;
    numFruits = 50;
    numTilesX = width / tileSize;
    numTilesY = height / tileSize;
    listFruits = {};
    gameLoop = true;
    snakeDirection = LEFT;
    srand((unsigned)time(NULL));

    snake = Snake(tileSize);

    this->renderer = *renderer;

    fillFruits();
    loop();
}

void Game::fillFruits()
{
    while (listFruits.size() < numFruits)
    {
        while (true)
        {
            int fruitX = rand() % numTilesX;
            int fruitY = rand() % numTilesY;
            vectorInt fruitPosition = vectorInt(fruitX * tileSize, fruitY * tileSize);

            if (!snake.checkFruitSpawnCollision(fruitPosition))
            {
                listFruits.push_back(Fruit(tileSize, fruitPosition));
                break;
            }
        }
    }
}

void Game::handleEvents()
{
    // Get next event
    SDL_Event event;
    bool updatedDirection = false;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            gameLoop = false;
            break;
        }
        else if (event.type == SDL_KEYDOWN && !updatedDirection)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                if (snakeDirection != DOWN)
                {
                    snakeDirection = UP;
                    updatedDirection = true;
                }
                break;
            case SDLK_DOWN:
                if (snakeDirection != UP)
                {
                    snakeDirection = DOWN;
                    updatedDirection = true;
                }
                break;
            case SDLK_LEFT:
                if (snakeDirection != RIGHT)
                {
                    snakeDirection = LEFT;
                    updatedDirection = true;
                }
                break;
            case SDLK_RIGHT:
                if (snakeDirection != LEFT)
                {
                    snakeDirection = RIGHT;
                    updatedDirection = true;
                }
                break;
            default:
                break;
            }
        }
    }
}

void Game::update()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    handleEvents();

    snake.move(snakeDirection);

    if (!snake.checkInBounds(width, height))
    {
        gameLoop = false;
    }

    if (!snake.checkNoSnakeCollision())
    {
        gameLoop = false;
    }

    std::list<Fruit>::iterator fruitItr;
    for (fruitItr = listFruits.begin(); fruitItr != listFruits.end(); fruitItr++)
    {
        Fruit fruit = *fruitItr;

        if (snake.canEatFruit(fruit.fruitPosition))
        {
            listFruits.erase(fruitItr);
            snake.addSegment();
            break;
        }
    }

    

    fillFruits();

    for (Fruit fruit : listFruits)
    {
        fruit.render(&renderer);
    }

    snake.render(&renderer);

    SDL_RenderPresent(renderer);
}

void Game::loop()
{
    while (gameLoop)
    {
        update();
        SDL_Delay(110);
    }
}