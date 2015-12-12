#include <GL/freeglut.h>
#include "timer.h"

void Timer::tick()
{
	int newTicks = glutGet(GLUT_ELAPSED_TIME);
	elapsedTicks = newTicks - lastTicks;
	lastTicks = newTicks;
}
