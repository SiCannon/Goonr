#include <GL/freeglut.h>
#include "keyboard.h"
#include "transform.h"
#include "defines.h"

bool keyState[256];

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

void handleInput(Transform *tf_world)
{
	if (keyState['a'])
	{
		tf_world->translate_x += TRANSLATE_INCREMENT;
	}
	if (keyState['d'])
	{
		tf_world->translate_x -= TRANSLATE_INCREMENT;
	}
	if (keyState['w'])
	{
		tf_world->translate_y -= TRANSLATE_INCREMENT;
	}
	if (keyState['s'])
	{
		tf_world->translate_y += TRANSLATE_INCREMENT;
	}
}