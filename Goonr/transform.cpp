#include "transform.h"


#include <GL/freeglut.h>

void Transform::apply()
{
	glScalef(scale, scale, scale);
	glTranslatef(translate_x, translate_y, 0);
}
