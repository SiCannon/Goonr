#pragma once

#include <GL/freeglut.h>
#include "transform.h"

class TestBuilding
{
	Transform *transform;
public:
	TestBuilding();
	~TestBuilding();
	void draw();
};
