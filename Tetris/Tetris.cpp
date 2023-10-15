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

	Uint64 start;
	Uint64 end;

	float elapsedMS;

	while (running)
	{
		start = SDL_GetPerformanceCounter();

		// handle events
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type)
			{
				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym) {
						case SDLK_UP:
							game.processKey(KEY_UP);
							break;

						case SDLK_LEFT:
							game.processKey(KEY_LEFT);
							break;

						case SDLK_RIGHT:
							game.processKey(KEY_RIGHT);
							break;

						case SDLK_DOWN:
							game.processKey(KEY_DOWN);
							break;
					}
					break;
				}
				case SDL_QUIT:
				{
					running = false;
					break;
				}
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


		end = SDL_GetPerformanceCounter();
		elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

		// Cap to 60 FPS
		SDL_Delay(floor(16.666f - elapsedMS));
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
