#include "Game.h"

Block::Block()
	: occupied(false), color{ 0, 0, 0 } {};

Block::Block(bool occupied, int color[3])
	: occupied(occupied), color{ color[0], color[1], color[2] } {};


Tetromino::Tetromino()
	: type(I), orientation(0), x(0), y(0) {};

Tetromino::Tetromino(TetrominoType type, int orientation, int x, int y)
	: type(type), orientation(orientation), x(x), y(y) {};


Game::Game()
	: currentTetromino(Tetromino(L, 0, 0, 0)) {};

void Game::update() {
	this->downCount++;

	if (this->downCount == 60) {
		this->downCount = 0;
		this->currentTetromino.y++;
	}


}
