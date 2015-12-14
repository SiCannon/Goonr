#include <GL/freeglut.h>
#include "transform.h"
#include "base_actor.h"

BaseActor::BaseActor(Timer *timer)
{
	this->timer = timer;
	
	transform = new Transform();
	transform->scale = 1.0f;
}

BaseActor::~BaseActor()
{
	delete(transform);
}

void BaseActor::draw()
{
	glPushMatrix();
	transform->applyTRS();
	draw_me();
	glPopMatrix();
}
