#include "keyboard.h"


void getKeyboardDown(unsigned char key, int x, int y)
{
	keyState[key] = true;

	if (key == 27)
	{
		glutLeaveMainLoop();
	}
}

void getKeyboardUp(unsigned char key, int x, int y)
{
	keyState[key] = false;
}

