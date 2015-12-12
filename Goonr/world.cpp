#include "world.h"

World::World()
{
	transform = new Transform();
}

World::~World()
{
	delete(transform);
}

void World::draw()
{
	transform->applyST();
}
