#include <GL/freeglut.h>
#include "highlight.h"
#include "screenutil.h"
#include "mouse.h"
#include "transform.h"

void Highlight::draw(Mouse *mouse, Transform *transform)
{
	GLfloat bx, by;
	getBoardPos(mouse, transform->scale, transform->translate_x, transform->translate_y, &bx, &by);

	glBegin(GL_LINE_LOOP);

	glColor3ub(255, 255, 255);
	GLfloat hx1 = bx + 0.1f;
	GLfloat hy1 = by + 0.1f;
	GLfloat hx2 = bx + 1.0f - 0.1f;
	GLfloat hy2 = by + 1.0f - 0.1f;
	glVertex2f(hx1, hy1);
	glVertex2f(hx2, hy1);
	glVertex2f(hx2, hy2);
	glVertex2f(hx1, hy2);

	glEnd();
}
