#include "defines.h"
#include <GL/freeglut.h>
#include "cursor.h"
#include "screenutil.h"
#include "mouse.h"

Cursor::Cursor(GLfloat cursorSize, Mouse *mouse)
{
	this->cursorSize = cursorSize;
	this->mouse = mouse;
}

void Cursor::draw()
{
	glLoadIdentity();

	GLfloat mx, my;
	screenToWorld(mouse->x, mouse->y, 1.0f, 0, 0, &mx, &my);

	glTranslatef(mx, my, 0);

	glColor3ub(32, 192, 0);
	glBegin(GL_QUADS);

	glVertex2f(0, 0);
	glVertex2f(cursorSize, -cursorSize * 2.0f);
	glVertex2f(cursorSize, -cursorSize);
	glVertex2f(cursorSize * 2.0f, -cursorSize);

	glEnd();
}
