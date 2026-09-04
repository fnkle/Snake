#include "game.hpp"
#include "Renderer.hpp"

int main()
{
    int width = 800;
    int height = 800;
	int tileSize = 40;

	Renderer renderer = Renderer("Snake", width, height, tileSize);

    Game game = Game(renderer, width/ tileSize, height / tileSize);
}
