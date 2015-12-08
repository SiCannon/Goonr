#include "testbuilding.h"

TestBuilding::TestBuilding()
{
	transform = new Transform();
	transform->translate_x = 150.0f;
	transform->translate_y = 100.0f;
	transform->scale = 1.0f;
}


TestBuilding::~TestBuilding()
{
	delete(transform);
}

void TestBuilding::draw()
{
	transform->rotation+=0.2f;

	glPushMatrix();
	transform->apply();

	glColor3ub(255, 255, 255);

	glBegin(GL_QUADS);                  // Each set of 4 vertices form a quad
	glVertex2f(-0.3f, -0.3f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(0.3f, 0.3f);
	glVertex2f(-0.3f, 0.3f);

	glPopMatrix();
}
