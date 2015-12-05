#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include "board.h"
#include "CellColors.h"

void Board::draw()//GLfloat scale, GLfloat translate_x, GLfloat translate_y)
{
	//glLoadIdentity();
	//glScalef(scale, scale, scale);
	//glTranslatef(translate_x, translate_y, 0);
	glBegin(GL_QUADS);
	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			drawCell(x, y);
		}
	}
	glEnd();
}

void Board::drawCell(int cx, int cy)
{
	Cell *cell = getcell(cx, cy);

	GLubyte cols[] = { 0, 0, 0 };
	getColorByCode(cell->color, cols, cell->state);
	glColor3ubv(cols);

	glVertex2f(cx, cy);
	glVertex2f(cx + 1.0f, cy);
	glVertex2f(cx + 1.0f, cy + 1.0f);
	glVertex2f(cx, cy + 1.0f);
}

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
