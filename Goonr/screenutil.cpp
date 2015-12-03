#include <GL/freeglut.h>
//#include "defines.h"
#include "screenutil.h"

#define orthoSize 10.0f

GLfloat rasterLeft = 0;
GLfloat rasterBottom = 0;
int windowWidth;
int windowHeight;

void reshape(int w, int h)
{
	windowWidth = w;
	windowHeight = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double aspect_ratio = (double)w / (double)h;
	glOrtho(-orthoSize * aspect_ratio, orthoSize * aspect_ratio, -orthoSize, orthoSize, -1, 1);

	rasterBottom = -orthoSize;
	rasterLeft = -orthoSize * aspect_ratio;
}

void screenToWorld(int x, int y, GLfloat scale, GLfloat trans_x, GLfloat trans_y, GLfloat *wx, GLfloat *wy)
{
	GLfloat aspect_ratio = (GLfloat)windowWidth / (GLfloat)windowHeight;
	GLfloat orthoHeight = orthoSize / scale;
	GLfloat orthoWidth = orthoHeight * aspect_ratio;

	*wx = 2.0f * orthoWidth * (GLfloat)x / (GLfloat)windowWidth - orthoWidth - trans_x;
	*wy = orthoHeight - 2.0f * orthoHeight * (GLfloat)y / (GLfloat)windowHeight - trans_y; // shouldn't this be  + trans_y ??
}
