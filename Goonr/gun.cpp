#include "gun.h"

Gun::Gun(int x, int y) : BaseActor()
{
	transform->scale = 1.0f;
	transform->rotation = 45.0f;
	setCell(x, y);
}

void Gun::draw_me()
{
	GLfloat gunSize = 0.6f;

	GLubyte cols[] = { 255, 255, 255 };
	glColor3ubv(cols);

	glBegin(GL_TRIANGLES);
	glVertex2f(0, gunSize / 2.0f);
	glVertex2f(-gunSize / 4.0f, -gunSize / 2.0f);
	glVertex2f(gunSize / 4.0f, -gunSize / 2.0f);
	glEnd();
}


void Gun::setCell(int x, int y)
{
	transform->translate_x = (float)x + 0.5f;
	transform->translate_y = (float)y + 0.5f;
}
