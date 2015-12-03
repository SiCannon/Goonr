#pragma once

#define RANDOM_SEED 165165165

#define CELL_TYPE_COUNT 4

#define CELL_BLUE 0
#define CELL_RED 1
#define CELL_YELLOW 2
#define CELL_GREEN 3

#define BOARD_WIDTH 300
#define BOARD_HEIGHT 200

struct Cell
{
	int color;
	int state;
};

class Board
{
	int width, height;
	Cell cells[BOARD_WIDTH][BOARD_HEIGHT];
	void generateSquares();
public:
	void init(int board_width, int board_height);
	Cell *getcell(int x, int y);
	
};

