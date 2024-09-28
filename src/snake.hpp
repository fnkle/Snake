#include <SDL2/SDL.h>
#include <list>
#include "Direction.hpp"
#include "vector.hpp"
#include "collisions.hpp"

class Snake
{
public:
    std::list<vectorInt> snakePiecesPos;
    int snakePieceSize;

    Snake(int snakePieceSize)
    {
        this->snakePieceSize = snakePieceSize;
        snakePiecesPos.push_back(vectorInt(400, 200));
        snakePiecesPos.push_back(vectorInt(400 + snakePieceSize, 200));
        snakePiecesPos.push_back(vectorInt(400 + snakePieceSize * 2, 200));
    }

    void move(enum Direction direction)
    {
        vectorInt newSnakeHead = snakePiecesPos.front();

        if (direction == UP)
        {
            newSnakeHead.y -= snakePieceSize;
        }
        else if (direction == DOWN)
        {
            newSnakeHead.y += snakePieceSize;
        }
        else if (direction == RIGHT)
        {
            newSnakeHead.x += snakePieceSize;
        }
        else if (direction == LEFT)
        {
            newSnakeHead.x -= snakePieceSize;
        }

        snakePiecesPos.pop_back();
        snakePiecesPos.push_front(newSnakeHead);
    }

    void addSegment()
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
                newSnakePiece.y += 40;
            }
            else
            {
                newSnakePiece.y -= 40;
            }
        }
        else if (penultimateSnakePiece.y == lastSnakePiece.y)
        {
            // CHeck whether it is going left or right
            if (penultimateSnakePiece.x - lastSnakePiece.x < 0)
            {
                newSnakePiece.x += 40;
            }
            else
            {
                newSnakePiece.x -= 40;
            }
        }
        snakePiecesPos.push_back(newSnakePiece);
    }

    bool checkInBounds(int width, int height)
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

    bool checkNoSnakeCollision()
    {
        std::list<vectorInt>::iterator snakeItr = snakePiecesPos.begin();
        snakeItr ++;
        for (snakeItr ; snakeItr != snakePiecesPos.end(); snakeItr++)
        {

            vectorInt snakePiece = *snakeItr;

            if (squareOnSquareCollision(snakePiecesPos.front(), snakePiece))
            {
                return false;
            }
        }
        return true;
    }
};