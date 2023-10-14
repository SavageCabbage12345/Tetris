// Tetris.cpp : Defines the entry point for the application.
//

#include <SDL.h>
#include "Tetris.h"

using namespace std;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	
	Game game;
	GameSDLRenderer gameSDLRenderer(&game);

	SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 800, 0);
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	bool running = true;
	while (running)
	{
		// handle events
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_KEYDOWN:
			{
				break;
			}
			case SDL_QUIT:
			{
				running = false;
				break;
			}
		}

		// process game
		game.update();

		// clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		// draw a point
		gameSDLRenderer.render(renderer);

		// flip buffers and display
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
