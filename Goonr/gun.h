#pragma once

#include <GL/freeglut.h>
#include "transform.h"

class Gun
{
	Transform *transform;
public:
	Gun();
	~Gun();
	void init();
	void draw();
};