#include <GL/freeglut.h>
#include "mouse.h"
#include "transform.h"

#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4

Mouse::Mouse(Transform *world_transform)
{
	this->world_transform = world_transform;

	onMouseLeftClick = nullptr;
	onMouseWheelUp = nullptr;
	onMouseWheelDown = nullptr;
}

void Mouse::set(int x, int y)
{
	this->x = x;
	this->y = y;
}


void Mouse::process(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (onMouseLeftClick != nullptr)
		{
			onMouseLeftClick(this);
		}
	}

	// Used for wheels, has to be up
	if (state == GLUT_UP)
	{
		if (button == GLUT_WHEEL_UP)
		{
			if (onMouseWheelUp != nullptr)
			{
				onMouseWheelUp(this);
			}
		}
		else if (button == GLUT_WHEEL_DOWN)
		{
			if (onMouseWheelDown != nullptr)
			{
				onMouseWheelDown(this);
			}
		}
	}
}
