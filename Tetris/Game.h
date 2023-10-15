#pragma once

#include <stdlib.h>
#include <time.h>

extern bool tetrominoShapes[7][4][4][4];

struct Block {
	bool occupied;
	int color[3];

	Block();

	Block(bool occupied, int color[3]);
};

enum Key {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

enum TetrominoShape {
	SHAPE_I, SHAPE_J, SHAPE_L, SHAPE_O, SHAPE_S, SHAPE_T, SHAPE_Z
};

struct Tetromino {
	TetrominoShape shape;
	int orientation;

	int last_x = NULL;
	int last_y = NULL;

	int x;
	int y;

	Tetromino();

	Tetromino(TetrominoShape type, int orientation, int x, int y);
};

class Game {
private:
	int rowDeleteCount = 0;
	bool clearingRows = false;
	int rowsToClear[4] = { 0, 0, 0, 0 };

	int downCount = 0;

	void checkForFullRows();

	void nextTetromino();
	void freezeCurrentTetromino();

	void processXAxisMove(int dir);
	void processDownMove();
	void processRotation();

public:
	Game();

	void update();
	void processKey(Key key);

	Block playspace[10][20];

	Tetromino currentTetromino;
};