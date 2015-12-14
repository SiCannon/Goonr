#pragma once

#include <GL/freeglut.h>
#include "transform.h"
#include "base_actor.h"
#include "timer.h"

class TestBuilding : public BaseActor
{
public:
	TestBuilding(Timer *timer, GLfloat x, GLfloat y, GLfloat scale, GLfloat speed);
protected:
	void draw_me();
private:
	GLfloat speed;
	GLfloat calcAngleInc();
};
