#pragma once

struct Block {
	bool occupied;
	int color[3];

	Block();

	Block(bool occupied, int color[3]);
};

enum TetrominoType {
	I, J, L, O, S, T, Z
};

struct Tetromino {
	TetrominoType type;
	int orientation;

	int x;
	int y;

	Tetromino();

	Tetromino(TetrominoType type, int orientation, int x, int y);
};

class Game {
private:
	int downCount = 0;

public:
	void update();
	Game();

	Block playspace[10][20];

	Tetromino currentTetromino;
};