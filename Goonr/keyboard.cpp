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
	GLfloat inc = TRANSLATE_INCREMENT / (tf_world->scale / 2.0f);
	if (keyState['a'])
	{
		tf_world->translate_x += inc;
	}
	if (keyState['d'])
	{
		tf_world->translate_x -= inc;
	}
	if (keyState['w'])
	{
		tf_world->translate_y -= inc;
	}
	if (keyState['s'])
	{
		tf_world->translate_y += inc;
	}
}
