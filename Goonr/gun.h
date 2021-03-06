#pragma once

#include <GL/freeglut.h>
#include "transform.h"
#include "base_actor.h"

class Gun : public BaseActor
{
public:
	Gun(Timer *timer, int x, int y);
	void setCell(int x, int y);
protected:
	void draw_me();
};
