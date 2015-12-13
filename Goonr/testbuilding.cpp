#include "testbuilding.h"
#include "timer.h"

TestBuilding::TestBuilding(Timer *timer, GLfloat x, GLfloat y, GLfloat scale, GLfloat speed) : BaseActor()
{
	this->timer = timer;
	transform->translate_x = x;
	transform->translate_y = y;
	transform->scale = scale;
	this->speed = speed;
}

void TestBuilding::draw_me()
{

	transform->rotation += calcAngleInc();

	glColor3ub(255, 255, 255);

	glBegin(GL_QUADS);
	glVertex2f(-0.3f, -0.3f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(0.3f, 0.3f);
	glVertex2f(-0.3f, 0.3f);
	glEnd();
}

GLfloat TestBuilding::calcAngleInc()
{
	GLfloat degreesPerSecond = speed;
	GLfloat degrees = degreesPerSecond * (timer->intervalTicks / 1000.0f);
	return degrees;
}
