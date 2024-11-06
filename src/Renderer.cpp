#include "Renderer.hpp"

#include "fruit.hpp"
#include "snake.hpp"

#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>

Renderer::Renderer(std::string title, int width, int height, int tileSize)
	: title(title), width(width), height(height), tileSize(tileSize)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error(
				"SDL Failed to initialise! SDL_Error: "
				+ std::string(SDL_GetError()));
	}

	window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_SHOWN);

	if (window == NULL) {
		throw std::runtime_error(
				"Window failed to initialise! SDL_Error: "
				+ std::string(SDL_GetError()));
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) {
		throw std::runtime_error(
				"Renderer failed to initialise! SDL_Error: "
				+ std::string(SDL_GetError()));
	}
}

void Renderer::clear() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
}

void Renderer::present() {
	SDL_RenderPresent(renderer);
}

void Renderer::renderSnake(const Snake* snake) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	for (vectorInt segment: snake->snakePiecesPos) {
		SDL_Rect bounds = {
			segment.x * tileSize,
			segment.y * tileSize,
			tileSize,
			tileSize
		};

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &bounds);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &bounds);
	}
}

void Renderer::renderFruits(std::list<Fruit> fruits) {
	for (Fruit fruit: fruits) {
		renderFruit(&fruit);
	}
}

void Renderer::renderFruit(const Fruit* fruit) {
	SDL_Rect bounds = {
		fruit->fruitPosition.x * tileSize,
		fruit->fruitPosition.y * tileSize,
		tileSize,
		tileSize,
	};

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &bounds);
}

void Renderer::setTitle(std::string title) {
	SDL_SetWindowTitle(window, title.c_str());
	this->title = title;
}

std::string Renderer::getTitle() {
	return title;
}
