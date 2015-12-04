#pragma once

class Cursor
{
	GLfloat cursorSize;
public:
	Cursor(GLfloat cursorSize);
	void draw(int mouse_x, int mouse_y);
};
