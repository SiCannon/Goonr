#pragma once

#include <GL/freeglut.h>
#include "transform.h"

class Gun
{
	Transform *transform;
public:
	Gun();
	~Gun();
	void setCell(int x, int y);
	void init();
	void draw();
};
