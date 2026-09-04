#include "game.hpp"
#include "fruit.hpp"
#include "Renderer.hpp"
#include "vector.hpp"

Game::Game(Renderer renderer, int numTilesX, int numTilesY)
	: renderer(renderer),
	numTilesX(numTilesX),
	numTilesY(numTilesY),
	snake(vectorInt())
{
    numFruits = 80;
    listFruits = {};
    gameLoop = true;
    snakeDirection = LEFT;
    srand((unsigned)time(NULL));

    snake = Snake({numTilesX / 2, numTilesY / 2});

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
            vectorInt fruitPosition = vectorInt(fruitX, fruitY);

            if (!snake.checkFruitSpawnCollision(fruitPosition))
            {
                listFruits.push_back(Fruit(fruitPosition));
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
    handleEvents();

    snake.move(snakeDirection);

    if (!snake.checkInBounds(numTilesX, numTilesY))
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

	renderer.clear();
	renderer.renderFruits(listFruits);
	renderer.renderSnake(&snake);
	renderer.present();
}

void Game::loop()
{
    while (gameLoop)
    {
        update();
        SDL_Delay(110);
    }
}
