#include "gun.h"

Gun::Gun()
{
	transform = new Transform();
}

Gun::~Gun()
{
	delete(transform);
}

void Gun::init()
{
}

void Gun::draw()
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);



	glEnd();
	glPopMatrix();

}
