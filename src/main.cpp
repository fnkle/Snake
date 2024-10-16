#include "game.hpp"
#include <SDL2/SDL.h>
#include <iostream>

int initSDL(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
{
    // Initialise SDL2 so we can use functions
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
        return -4;
    }
    else
    {
        // Create window
        *window = SDL_CreateWindow("Simulations", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                   SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            std::cout << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
            return -1;
        }

        *renderer = SDL_CreateRenderer(*window, -1, 0);
        if (renderer == NULL)
        {

            std::cout << "Renderer could not be created! SDL_Error: %s\n", SDL_GetError();
            return -2;
        }

        return 1;
    }
}

int main()
{
    int width = 800;
    int height = 800;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int init = initSDL(&window, &renderer, width, height);

    if (init)
    {
        Game game = Game(&renderer, width, height);
    }
}
