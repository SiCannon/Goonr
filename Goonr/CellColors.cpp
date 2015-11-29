#include <GL/freeglut.h>
#include "CellColors.h"
#include "board.h"

#define k1 128
#define k2 32

#define k1b 255
#define k2b 32

void getColorByCode(int colorCode, GLubyte *colors, int state)
{
	int c1 = (state == 0) ? k1 : k1b;
	int c2 = (state == 0) ? k2 : k2b;


	switch (colorCode)
	{
		case CELL_RED:
			colors[0] = c1;
			colors[1] = c2;
			colors[2] = c2;
			break;
		case CELL_BLUE:
			colors[0] = c2;
			colors[1] = c2;
			colors[2] = c1;
			break;
		case CELL_YELLOW:
			colors[0] = c1;
			colors[1] = c1;
			colors[2] = c2;
			break;
		case CELL_GREEN:
			colors[0] = c2;
			colors[1] = c1;
			colors[2] = c2;
			break;
		default:
			colors[0] = c1;
			colors[1] = c1;
			colors[2] = c2;
			break;
	}
}