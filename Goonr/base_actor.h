#pragma once
#include "transform.h"

class BaseActor
{
public:
	Transform *transform;
	BaseActor();
	~BaseActor();
	void draw();
protected:
	virtual void draw_me() =0;
};
