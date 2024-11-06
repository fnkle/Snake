#include "snake.hpp"
#include "collisions.hpp"
#include "vector.hpp"

Snake::Snake(vectorInt startPos)
{
    snakePiecesPos.push_back(startPos);
    snakePiecesPos.push_back(vectorInt(startPos.x + 1, startPos.y));
    snakePiecesPos.push_back(vectorInt(startPos.x, startPos.y));
}

void Snake::move(enum Direction direction)
{
    vectorInt newSnakeHead = snakePiecesPos.front();

    if (direction == UP)
    {
        newSnakeHead.y--;
    }
    else if (direction == DOWN)
    {
        newSnakeHead.y++;
    }
    else if (direction == RIGHT)
    {
        newSnakeHead.x++;
    }
    else if (direction == LEFT)
    {
        newSnakeHead.x--;
    }

    snakePiecesPos.pop_back();
    snakePiecesPos.push_front(newSnakeHead);
}

void Snake::addSegment()
{
    vectorInt lastSnakePiece = snakePiecesPos.back();
    vectorInt penultimateSnakePiece = *(snakePiecesPos.end()--);
    vectorInt newSnakePiece = snakePiecesPos.back();

    // If the x position hasnt change it means the snake is traveling up or down
    if (penultimateSnakePiece.x == lastSnakePiece.x)
    {
        // Check whether it is going up or down
        if (penultimateSnakePiece.y - lastSnakePiece.y < 0)
        {
            newSnakePiece.y++;
        }
        else
        {
            newSnakePiece.y--;
        }
    }
    else if (penultimateSnakePiece.y == lastSnakePiece.y)
    {
        // CHeck whether it is going left or right
        if (penultimateSnakePiece.x - lastSnakePiece.x < 0)
        {
            newSnakePiece.x++;
        }
        else
        {
            newSnakePiece.x--;
        }
    }
    snakePiecesPos.push_back(newSnakePiece);
}

bool Snake::checkInBounds(int width, int height)
{
    vectorInt frontPiece = this->snakePiecesPos.front();

    if (frontPiece.x < 0 || frontPiece.x >= width)
    {
        return false;
    }
    else if (frontPiece.y < 0 || frontPiece.y >= height)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Snake::checkNoSnakeCollision()
{
    std::list<vectorInt>::iterator snakeItr = snakePiecesPos.begin();
    snakeItr++;
    for (snakeItr; snakeItr != snakePiecesPos.end(); snakeItr++)
    {
        vectorInt snakePiece = *snakeItr;

        if (tileCollision(snakePiecesPos.front(), snakePiece))
        {
            return false;
        }
    }
    return true;
}

bool Snake::checkFruitSpawnCollision(vectorInt fruitPosition)
{
    for (vectorInt snakePiecePos : snakePiecesPos)
    {
        if (tileCollision(fruitPosition, snakePiecePos))
        {
            return true;
        }
    }
    return false;
}

bool Snake::canEatFruit(vectorInt fruitPosition)
{
    if(tileCollision(fruitPosition, snakePiecesPos.front())){
        return true;
    }
    return false;
}
