#include "testbuilding.h"

TestBuilding::TestBuilding(GLfloat x, GLfloat y, GLfloat scale)
{
	transform = new Transform();
	transform->translate_x = x;
	transform->translate_y = y;
	transform->scale = scale;
}


TestBuilding::~TestBuilding()
{
	delete(transform);
}

void TestBuilding::draw()
{
	transform->rotation+=0.2f;

	glPushMatrix();
	transform->applyTRS();

	glColor3ub(255, 255, 255);

	glBegin(GL_QUADS);                  // Each set of 4 vertices form a quad
	glVertex2f(-0.3f, -0.3f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(0.3f, 0.3f);
	glVertex2f(-0.3f, 0.3f);
	glEnd();

	glPopMatrix();
}
