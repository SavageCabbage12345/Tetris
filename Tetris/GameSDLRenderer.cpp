#include "GameSDLRenderer.h"

bool tetrominoShapes[7][4][4][4] =
{ {{{0,1,0,0},
	{0,1,0,0},
	{0,1,0,0},
	{0,1,0,0}},
   {{0,0,0,0},
	{1,1,1,1},
	{0,0,0,0},
	{0,0,0,0}},
   {{0,0,1,0},
	{0,0,1,0},
	{0,0,1,0},
	{0,0,1,0}},
   {{0,0,0,0},
	{0,0,0,0},
	{1,1,1,1},
	{0,0,0,0}}},
  {{{0,1,0,0},
	{0,1,0,0},
	{1,1,0,0},
	{0,0,0,0}},
   {{1,0,0,0},
	{1,1,1,0},
	{0,0,0,0},
	{0,0,0,0}},
   {{0,1,1,0},
	{0,1,0,0},
	{0,1,0,0},
	{0,0,0,0}},
   {{0,0,0,0},
	{1,1,1,0},
	{0,0,1,0},
	{0,0,0,0}}},
  {{{0,1,0,0},
	{0,1,0,0},
	{0,1,1,0},
	{0,0,0,0}},
   {{0,0,0,0},
	{1,1,1,0},
	{1,0,0,0},
	{0,0,0,0}},
   {{1,1,0,0},
	{0,1,0,0},
	{0,1,0,0},
	{0,0,0,0}},
   {{0,0,1,0},
	{1,1,1,0},
	{0,0,0,0},
	{0,0,0,0}}},
  {{{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}},
   {{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}},
   {{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}},
   {{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}}},
  {{{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0}},
   {{0,1,0,0},
	{0,1,1,0},
	{0,0,1,0},
	{0,0,0,0}},
   {{0,0,0,0},
	{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0}},
   {{1,0,0,0},
	{1,1,0,0},
	{0,1,0,0},
	{0,0,0,0}}},
  {{{0,1,0,0},
	{1,1,1,0},
	{0,0,0,0},
	{0,0,0,0}},
   {{0,1,0,0},
	{0,1,1,0},
	{0,1,0,0},
	{0,0,0,0}},
   {{0,0,0,0},
	{1,1,1,0},
	{0,1,0,0},
	{0,0,0,0}},
   {{0,1,0,0},
	{1,1,0,0},
	{0,1,0,0},
	{0,0,0,0}}},
  {{{1,1,0,0},
	{0,1,1,0},
	{0,0,0,0},
	{0,0,0,0}},
   {{0,0,1,0},
	{0,1,1,0},
	{0,1,0,0},
	{0,0,0,0}},
   {{0,0,0,0},
	{1,1,0,0},
	{0,1,1,0},
	{0,0,0,0}},
   {{0,1,0,0},
	{1,1,0,0},
	{1,0,0,0},
	{0,0,0,0}} } };

GameSDLRenderer::GameSDLRenderer(Game* game)
	: game(game){}

void GameSDLRenderer::render(SDL_Renderer* renderer) {
	SDL_Rect rect;

	int height;
	int width;

	SDL_GetRendererOutputSize(renderer, &width, &height);

	int squareLength = (width / 10);

	for (int y = 0; y < 20; ++y) {
		for (int x = 0; x < 10; ++x) {
			if (!this->game->playspace[x][y].occupied)
				continue;

			rect = SDL_Rect(x * squareLength, y * squareLength, squareLength, squareLength);

			SDL_SetRenderDrawColor(renderer, this->game->playspace[x][y].color[0], this->game->playspace[x][y].color[1], this->game->playspace[x][y].color[2], 255);
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	int tetrominoX = this->game->currentTetromino.x;
	int tetrominoY = this->game->currentTetromino.y;
	auto currentTetrominoShape = tetrominoShapes[this->game->currentTetromino.type][this->game->currentTetromino.orientation];

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (!currentTetrominoShape[y][x])
				continue;

			rect = SDL_Rect((tetrominoX + x) * squareLength, (tetrominoY + y) * squareLength, squareLength, squareLength);

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}
