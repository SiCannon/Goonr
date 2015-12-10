#pragma once

#include <GL/freeglut.h>
#include "transform.h"

class TestBuilding
{
	Transform *transform;
public:
	TestBuilding(GLfloat x, GLfloat y, GLfloat scale);
	~TestBuilding();
	void draw();
};
