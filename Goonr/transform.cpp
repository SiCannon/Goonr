#include <GL/freeglut.h>
#include "transform.h"

void Transform::applyTRS()
{
	glTranslatef(translate_x, translate_y, 0);
	glRotatef(rotation, 0, 0, 1.0f);
	glScalef(scale, scale, scale);
}

void Transform::applyST()
{
	glScalef(scale, scale, scale);
	glTranslatef(translate_x, translate_y, 0);
}
