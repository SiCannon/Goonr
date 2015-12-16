#include <math.h>
#include <GL/freeglut.h>
#include "planet.h"

Planet::Planet(Timer *timer) : BaseActor(timer)
{
	angle = 0.0f;
}

/*
Planet::~Planet()
{
}*/

#define SLICES 24

void Planet::draw_me()
{
	//transform->rotation -= 0.5f;
	transform->scale = fabs(sin((GLfloat)timer->totalTicks / 200.0f) / 10.0f) + 1.0f;

	GLfloat innerRadius = 2.0f;
	GLfloat outerRadius = 2.1f;

	glColor3ub(192, 0, 192);

	glBegin(GL_TRIANGLE_STRIP);

	for (int t = 0; t <= SLICES; t++)
	{
		GLfloat theta = ((GLfloat)t / (GLfloat)SLICES) * 6.284;
		GLfloat x = innerRadius * sin(theta);
		GLfloat y = innerRadius * cos(theta);
		glVertex2f(x, y);
		x = outerRadius * sin(theta);
		y = outerRadius * cos(theta);
		glVertex2f(x, y);
	}

	glEnd();
}
