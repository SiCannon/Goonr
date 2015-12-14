#pragma once

#include "base_actor.h"

class Monster : public BaseActor
{
public:
	Monster(Timer *timer);
	void update();
protected:
	void draw_me();
};
