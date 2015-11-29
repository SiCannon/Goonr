#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void Board::generateSquares()
{
	srand(RANDOM_SEED);

	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			cells[x][y].color = rand() % CELL_TYPE_COUNT;
		}
	}
}

void Board::init(int board_width, int board_height)
{
	width = board_width;
	height = board_height;
	generateSquares();
}

Cell *Board::getcell(int x, int y)
{
	return &cells[x][y];
}
