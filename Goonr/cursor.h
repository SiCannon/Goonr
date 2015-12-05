#pragma once

#include "mouse.h"

class Cursor
{
	GLfloat cursorSize;
	Mouse *mouse;
public:
	Cursor(GLfloat cursorSize, Mouse *mouse);
	void draw();
};
