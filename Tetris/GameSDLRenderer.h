#pragma once

#include <SDL.h>
#include "Game.h"

extern int tetrominoRenderColors[7][4];

class GameSDLRenderer {
private:
	Game* game;

public:
	GameSDLRenderer(Game* game);

	void render(SDL_Renderer* renderer);
};