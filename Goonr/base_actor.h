#pragma once
#include "transform.h"
#include "timer.h"

class BaseActor
{
public:
	Transform *transform;
	BaseActor(Timer *timer);
	~BaseActor();
	void draw();
	virtual void update() { }
protected:
	Timer *timer;
	virtual void draw_me() =0;
};
