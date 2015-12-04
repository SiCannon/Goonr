#include "defines.h"
#include <GL/freeglut.h>
#include "cursor.h"
#include "screenutil.h"

Cursor::Cursor(GLfloat cursorSize)
{
	this->cursorSize = cursorSize;
}

void Cursor::draw(int mouse_x, int mouse_y)
{
	glLoadIdentity();

	GLfloat mx, my;
	screenToWorld(mouse_x, mouse_y, 1.0f, 0, 0, &mx, &my);

	glTranslatef(mx, my, 0);

	glColor3ub(32, 192, 0);
	glBegin(GL_QUADS);

	glVertex2f(0, 0);
	glVertex2f(cursorSize, -cursorSize * 2.0f);
	glVertex2f(cursorSize, -cursorSize);
	glVertex2f(cursorSize * 2.0f, -cursorSize);

	glEnd();
}
