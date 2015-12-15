#pragma once
#include "base_actor.h"
#include "timer.h"

class Planet : public BaseActor
{
public:
	Planet(Timer *timer);
	~Planet();
protected:
	void draw_me();
};

