#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "fruit.hpp"
#include "snake.hpp"

#include <list>
#include <string>

#include <SDL2/SDL.h>

class Renderer
{
	private:
		SDL_Renderer *renderer;
		SDL_Window *window;
		std::string title;
		int width;
		int height;
		int tileSize;
	
	public:
		Renderer(std::string title, int width, int height, int tileSize);

		void clear();
		void present();
		void renderSnake(const Snake* snake);
		void renderFruits(std::list<Fruit> fruits);
		void renderFruit(const Fruit* fruit);

		void setTitle(std::string title);

		std::string getTitle();
};

#endif
