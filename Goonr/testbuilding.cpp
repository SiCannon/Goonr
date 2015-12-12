#include "testbuilding.h"

TestBuilding::TestBuilding(GLfloat x, GLfloat y, GLfloat scale) : BaseActor()
{
	transform->translate_x = x;
	transform->translate_y = y;
	transform->scale = scale;
}

void TestBuilding::draw_me()
{
	transform->rotation+=0.2f;

	glColor3ub(255, 255, 255);

	glBegin(GL_QUADS);
	glVertex2f(-0.3f, -0.3f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(0.3f, 0.3f);
	glVertex2f(-0.3f, 0.3f);
	glEnd();
}
