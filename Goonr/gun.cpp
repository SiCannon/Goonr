#include "gun.h"

Gun::Gun()
{
	transform = new Transform();
	transform->scale = 1.0f;
}

Gun::~Gun()
{
	delete(transform);
}

void Gun::init()
{
}

void Gun::draw()
{
	glPushMatrix();
	transform->apply();
	glBegin(GL_TRIANGLES);

	GLfloat gunSize = 0.6f;

	GLubyte cols[] = { 255, 255, 255 };
	glColor3ubv(cols);

	glVertex2f(0, gunSize / 2.0f);
	glVertex2f(-gunSize / 4.0f, -gunSize / 2.0f);
	glVertex2f(gunSize / 4.0f, -gunSize / 2.0f);


	glEnd();
	glPopMatrix();

	//glPushMatrix();                     // Save model-view matrix setting
	//glLoadIdentity();
	//glTranslatef(-0.5f, 0.4f, 0.0f);    // Translate
	//glScalef(2.0f, 2.0f, 2.0f);
	/*
	glRotatef(30.0f, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
	glBegin(GL_QUADS);                  // Each set of 4 vertices form a quad
	glColor3ub(255, 255, 255);
	glVertex2f(-0.3f, -0.3f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(0.3f, 0.3f);
	glVertex2f(-0.3f, 0.3f);
	glEnd();
	*/
	//glPopMatrix();
}


void Gun::setCell(int x, int y)
{
	transform->translate_x = (float)x + 0.5f;
	transform->translate_y = (float)y + 0.5f;
}
