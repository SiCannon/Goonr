#include "transform.h"


#include <GL/freeglut.h>

void Transform::apply()
{
	glTranslatef(translate_x, translate_y, 0);
	glRotatef(rotation, 0, 0, 1.0f);
	glScalef(scale, scale, scale);
}
