#include <freeglut.h>
#include "CellColors.h"
#include "board.h"

#define k1 128
#define k2 32

void getColorByCode(int colorCode, GLubyte *colors)
{
	switch (colorCode)
	{
		case CELL_RED:
			colors[0] = k1;
			colors[1] = k2;
			colors[2] = k2;
			break;
		case CELL_BLUE:
			colors[0] = k2;
			colors[1] = k2;
			colors[2] = k1;
			break;
		case CELL_YELLOW:
			colors[0] = k1;
			colors[1] = k1;
			colors[2] = k2;
			break;
		case CELL_GREEN:
			colors[0] = k2;
			colors[1] = k1;
			colors[2] = k2;
			break;
		default:
			colors[0] = k1;
			colors[1] = k1;
			colors[2] = k2;
			break;
	}
}