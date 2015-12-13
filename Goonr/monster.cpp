#include <GL/freeglut.h>
#include "base_actor.h"
#include "monster.h"

Monster::Monster() : BaseActor()
{
	
}

void Monster::draw_me()
{
	GLubyte cols[] = { 0, 102, 255 };
	glColor3ubv(cols);

	GLfloat monster_size = 0.1f;

	glBegin(GL_TRIANGLES);
	glVertex2f(0, monster_size / 2.0f);
	glVertex2f(-monster_size / 4.0f, -monster_size / 2.0f);
	glVertex2f(monster_size / 4.0f, -monster_size / 2.0f);
	glEnd();
}
