#include "world.h"

void World::World()
{
	transform = new Transform();
}

void World::~World()
{
	delete(transform);
}

void draw()
{
	transform->applySF();
}
