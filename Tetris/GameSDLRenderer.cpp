#include "GameSDLRenderer.h"

int tetrominoRenderColors[7][4] = { {249, 65, 68, 255 }, {243, 114, 44, 255 }, {248, 150, 30, 255 }, {249, 199, 79, 255 }, {144, 190, 109, 255 }, { 67, 170, 139, 255 }, {87, 117, 144, 255} };

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

			auto color = tetrominoRenderColors[this->game->playspace[x][y].sourceShape];

			SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
			SDL_RenderFillRect(renderer, &rect);


			rect = SDL_Rect(x * squareLength + squareLength * 0.2, y * squareLength + squareLength * 0.2, squareLength*0.6, squareLength*0.6);

			SDL_SetRenderDrawColor(renderer, color[0] * 0.8, color[1] * 0.8, color[2] * 0.8, color[3]);
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	int tetrominoX = this->game->currentTetromino.x;
	int tetrominoY = this->game->currentTetromino.y;
	auto currentTetrominoShape = tetrominoShapes[this->game->currentTetromino.shape][this->game->currentTetromino.orientation];

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (!currentTetrominoShape[y][x])
				continue;

			rect = SDL_Rect((tetrominoX + x) * squareLength, (tetrominoY + y) * squareLength, squareLength, squareLength);

			auto color = tetrominoRenderColors[this->game->currentTetromino.shape];

			SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
			SDL_RenderFillRect(renderer, &rect);

			rect = SDL_Rect((tetrominoX + x) * squareLength + squareLength * 0.2, (tetrominoY + y) * squareLength + squareLength * 0.2, squareLength * 0.6, squareLength * 0.6);

			SDL_SetRenderDrawColor(renderer, color[0] * 0.8, color[1] * 0.8, color[2] * 0.8, color[3]);
			SDL_RenderFillRect(renderer, &rect);

			/*if ((x < 3) && currentTetrominoShape[y][x + 1]) {
				rect = SDL_Rect((tetrominoX + x) * squareLength + squareLength * 0.8, (tetrominoY + y) * squareLength + squareLength * 0.2, squareLength * 0.2, squareLength * 0.6);

				SDL_SetRenderDrawColor(renderer, color[0] * 0.8, color[1] * 0.8, color[2] * 0.8, color[3]);
				SDL_RenderFillRect(renderer, &rect);
			}
			if ((x > 0) && currentTetrominoShape[y][x - 1]) {
				rect = SDL_Rect((tetrominoX + x) * squareLength, (tetrominoY + y) * squareLength + squareLength * 0.2, squareLength * 0.2, squareLength * 0.6);

				SDL_SetRenderDrawColor(renderer, color[0] * 0.8, color[1] * 0.8, color[2] * 0.8, color[3]);
				SDL_RenderFillRect(renderer, &rect);
			}
			if ((y < 3) && currentTetrominoShape[y + 1][x]) {
				rect = SDL_Rect((tetrominoX + x) * squareLength + squareLength * 0.2, (tetrominoY + y) * squareLength + squareLength * 0.8, squareLength * 0.6, squareLength * 0.2);

				SDL_SetRenderDrawColor(renderer, color[0] * 0.8, color[1] * 0.8, color[2] * 0.8, color[3]);
				SDL_RenderFillRect(renderer, &rect);
			}
			if ((y > 0) && currentTetrominoShape[y - 1][x]) {
				rect = SDL_Rect((tetrominoX + x) * squareLength + squareLength * 0.2, (tetrominoY + y) * squareLength, squareLength * 0.6, squareLength * 0.2);

				SDL_SetRenderDrawColor(renderer, color[0] * 0.8, color[1] * 0.8, color[2] * 0.8, color[3]);
				SDL_RenderFillRect(renderer, &rect);
			}*/
		}
	}
}
