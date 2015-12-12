#pragma once

#include <GL/freeglut.h>
#include "transform.h"
#include "base_actor.h"

class TestBuilding : public BaseActor
{
public:
	TestBuilding(GLfloat x, GLfloat y, GLfloat scale);
protected:
	void draw_me();
};
