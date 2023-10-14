#pragma once

#include <SDL.h>
#include "Game.h"

class GameSDLRenderer {
private:
	Game* game;

public:
	GameSDLRenderer(Game* game);

	void render(SDL_Renderer* renderer);
};