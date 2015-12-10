#pragma once

#include "transform.h"

class World
{
public:
	Transform* transform; 
	World();
	~World();
	void draw();
}
