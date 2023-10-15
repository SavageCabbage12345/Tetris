#include "Game.h"

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

Block::Block()
	: occupied(false), color{ 0, 0, 0 } {};

Block::Block(bool occupied, int color[3])
	: occupied(occupied), color{ color[0], color[1], color[2] } {};


Tetromino::Tetromino()
	: shape(SHAPE_I), orientation(0), x(0), y(0) {};

Tetromino::Tetromino(TetrominoShape type, int orientation, int x, int y)
	: shape(type), orientation(orientation), x(x), y(y) {};


Game::Game()
	: currentTetromino(Tetromino(TetrominoShape(rand() % 7), rand() % 4, 0, 0)) {
	srand(time(NULL));
};

void Game::checkForFullRows() {
	bool fullRows[4] = { 0, 0, 0, 0 };

	for (int checkRow = currentTetromino.y; (checkRow < (currentTetromino.y + 4)) && (checkRow < 20); ++checkRow) {
		fullRows[checkRow - currentTetromino.y] = true;
		for (int checkCol = 0; checkCol < 10; ++checkCol) {
			if (!this->playspace[checkCol][checkRow].occupied) {
				this->rowsToClear[checkRow - currentTetromino.y] = checkRow;
				break;
			}
		}
		if (fullRows[checkRow - currentTetromino.y])
			this->clearingRows = true;
	}
}

void Game::nextTetromino() {
	this->currentTetromino = Tetromino(TetrominoShape(rand() % 7), rand() % 4, 0, 0);
}

void Game::freezeCurrentTetromino() {
	auto currentTetrominoShape = tetrominoShapes[this->currentTetromino.shape][this->currentTetromino.orientation];

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (!currentTetrominoShape[y][x])
				continue;

			this->playspace[this->currentTetromino.x + x][this->currentTetromino.y + y].occupied = true;
			this->playspace[this->currentTetromino.x + x][this->currentTetromino.y + y].color[0] = 255;
			this->playspace[this->currentTetromino.x + x][this->currentTetromino.y + y].color[1] = 255;
			this->playspace[this->currentTetromino.x + x][this->currentTetromino.y + y].color[2] = 255;
		}
	}

	checkForFullRows();

	nextTetromino();
}

void Game::processXAxisMove(int dir) {
	this->currentTetromino.x += dir;
	
	auto currentTetrominoShape = tetrominoShapes[this->currentTetromino.shape][this->currentTetromino.orientation];

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (!currentTetrominoShape[y][x])
				continue;

			if ((this->currentTetromino.x + x) < 0) {
				this->currentTetromino.x -= this->currentTetromino.x + x;
			}

			if ((this->currentTetromino.x + x) >= 10) {
				this->currentTetromino.x = 9 - x;
			}

			if (this->playspace[this->currentTetromino.x + x][this->currentTetromino.y + y].occupied) {
				this->currentTetromino.x -= dir;
			}
		}
	}
}

void Game::processDownMove() {
	this->currentTetromino.last_y = this->currentTetromino.y;
	this->currentTetromino.y++;

	auto currentTetrominoShape = tetrominoShapes[this->currentTetromino.shape][this->currentTetromino.orientation];

	for (int y = 3; y >= 0; --y) {
		for (int x = 0; x < 4; ++x) {
			if (!currentTetrominoShape[y][x])
				continue;

			if (((this->currentTetromino.y + y) >= 20) ||
				this->playspace[this->currentTetromino.x + x][this->currentTetromino.y + y].occupied) {
				this->currentTetromino.y--;
				freezeCurrentTetromino();
				return;
			}
		}
	}
}

void Game::processRotation() {
	this->currentTetromino.orientation = (this->currentTetromino.orientation + 1) % 4;

	auto currentTetrominoShape = tetrominoShapes[this->currentTetromino.shape][this->currentTetromino.orientation];

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (!currentTetrominoShape[y][x])
				continue;

			if (((this->currentTetromino.x + x) < 0) ||
				((this->currentTetromino.x + x) >= 10) ||
				this->playspace[this->currentTetromino.x + x][this->currentTetromino.y + y].occupied) {
				this->currentTetromino.x -= ((x / 2) * 2) - 1;
			}
		}
	}

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (!currentTetrominoShape[y][x])
				continue;

			if ((this->currentTetromino.y + y) >= 20){
				this->currentTetromino.orientation = (this->currentTetromino.orientation - 1) % 4;
				this->currentTetromino.x = this->currentTetromino.last_x;
				return;
			}
		}
	}

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (!currentTetrominoShape[y][x])
				continue;

			if (((this->currentTetromino.x + x) < 0) ||
				((this->currentTetromino.x + x) >= 10) ||
				this->playspace[this->currentTetromino.x + x][this->currentTetromino.y + y].occupied) {
				this->currentTetromino.orientation = (this->currentTetromino.orientation - 1) % 4;
				this->currentTetromino.x = this->currentTetromino.last_x;
				return;
			}
		}
	}
}

void Game::update() {
	this->currentTetromino.last_x = this->currentTetromino.x;
	this->currentTetromino.last_y = this->currentTetromino.y;

	if (this->clearingRows) {
		/*for (int eraseRow = currentTetromino.y; eraseRow < (currentTetromino.y + 4); ++eraseRow) {
			if (!fullRows[eraseRow - currentTetromino.y])
				continue;
			for (int eraseCol = 0; eraseCol < 10; ++eraseCol) {
				this->playspace[eraseCol][eraseRow].occupied = false;
			}
		}

		for (int erasedRow = currentTetromino.y; erasedRow < (currentTetromino.y + 4); ++erasedRow) {
			if (!fullRows[erasedRow - currentTetromino.y])
				continue;
			for (int moveRow = erasedRow; moveRow > 0; --moveRow) {
				for (int moveCol = 0; moveCol < 10; ++moveCol) {
					this->playspace[moveCol][moveRow].occupied = this->playspace[moveCol][moveRow - 1].occupied;
				}
			}
		}*/
	}

	this->downCount++;

	if (this->downCount == 60) {
		this->downCount = 0;

		Game::processDownMove();
	}
}

void Game::processKey(Key key) {
	this->currentTetromino.last_x = this->currentTetromino.x;
	this->currentTetromino.last_y = this->currentTetromino.y;

	switch (key) {
		case KEY_UP:
			this->processRotation();
			break;

		case KEY_LEFT:
			this->processXAxisMove(-1);
			break;

		case KEY_RIGHT:
			this->processXAxisMove(1);
			break;

		case KEY_DOWN:
			this->processDownMove();
			break;
	}
}