#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#include "defines.h"
#include "textutils.h"
#include "CellColors.h"
#include "board.h"

#include "transform.h"
#include "screenutil.h"
#include "cursor.h"
#include "mouse.h"
#include "util.h"

bool keyState[256];
GLfloat angle = 0.0f;

Board* board;
Transform* tf_world;
Transform* tf_cursor;
Cursor *cursor;
Mouse *mouse;

void display()
{
	if (keyState['a'])
	{
		tf_world->translate_x += translateIncrement;
	}
	if (keyState['d'])
	{
		tf_world->translate_x -= translateIncrement;
	}
	if (keyState['w'])
	{
		tf_world->translate_y -= translateIncrement;
	}
	if (keyState['s'])
	{
		tf_world->translate_y += translateIncrement;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	
	tf_world->apply();

	board->draw();

	GLfloat bx, by;
	getBoardPos(mouse, tf_world->scale, tf_world->translate_x, tf_world->translate_y, &bx, &by);

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

	/* draw a rotating square * /
	glPushMatrix();                     // Save model-view matrix setting
	glLoadIdentity();
	//glTranslatef(-0.5f, 0.4f, 0.0f);    // Translate
	glScalef(2.0f, 2.0f, 2.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
	glBegin(GL_QUADS);                  // Each set of 4 vertices form a quad
	glColor3ub(255, 255, 255);
	glVertex2f(-0.3f, -0.3f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(0.3f, 0.3f);
	glVertex2f(-0.3f, 0.3f);
	glEnd();
	glPopMatrix();
	angle += 1.0f; //*/

	cursor->draw();

	glPopMatrix();

	//GLfloat s = (2.0f * orthoSize) / scale;
	//printFloat(true, rasterLeft, 0, s, 192, 192, 192);

	printInt(true, rasterLeft, rasterBottom, mouse->x, 128, 128, 0);
	printText(false, 0, 0, ", ", 128, 128, 0);
	printInt(false, 0, 0, mouse->y, 128, 128, 0);

	printText(false, 0, 0, " - ", 128, 128, 0);
	printFloat(false, 0, 0, tf_world->scale, 128, 128, 0);

	printText(false, 0, 0, " - ", 128, 128, 0);
	printFloat(false, 0, 0, tf_world->translate_x, 128, 128, 0);


	glutSwapBuffers();
	glutPostRedisplay();
}

void saveMousePosition(int x, int y)
{
	mouse->set(x, y);
}

void processMouse(int button, int state, int x, int y)
{
	mouse->process(button, state, x, y);
}

void mouseLeftClick(Mouse *mouse)
{
	GLfloat bx, by;
	getBoardPos(mouse, tf_world->scale, tf_world->translate_x, tf_world->translate_y, &bx, &by);
	Cell *cell = board->getcell(bx, by);
	cell->state = (cell->state == 0) ? 1 : 0;
}

void mouseWheelUp(Mouse *mouse)
{
	tf_world->scale += scaleIncrement;
}

void mouseWheelDown(Mouse *mouse)
{
	if (tf_world->scale > 0)
	{
		tf_world->scale -= scaleIncrement;
	}
}

void getKeyboardDown(unsigned char key, int x, int y)
{
	keyState[key] = true;

	if (key == 27)
	{
		glutLeaveMainLoop();
	}
}

void getKeyboardUp(unsigned char key, int x, int y)
{
	keyState[key] = false;
}

int main(int argc, char **argv)
{
	board = new Board();
	board->init(10, 10);

	tf_world = new Transform();
	tf_world->scale = initialScale;
	tf_world->translate_x = (-BOARD_WIDTH / 2.0f);
	tf_world->translate_y = (-BOARD_HEIGHT / 2.0f);

	tf_cursor = new Transform();
	tf_cursor->scale = 1.0f;
	tf_cursor->translate_x = 0;
	tf_cursor->translate_y = 0;


	mouse = new Mouse();
	mouse->onMouseLeftClick = &mouseLeftClick;
	mouse->onMouseWheelUp = &mouseWheelUp;
	mouse->onMouseWheelDown = &mouseWheelDown;

	cursor = new Cursor(CURSOR_SIZE, mouse);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glEnable(GL_MULTISAMPLE);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(intialWindowWidth, intialWindowHeight);
	glutCreateWindow("Goonr");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(saveMousePosition);
	glutMotionFunc(saveMousePosition);
	glutMouseFunc(processMouse);
	glutKeyboardFunc(getKeyboardDown);
	glutKeyboardUpFunc(getKeyboardUp);
	glutSetCursor(GLUT_CURSOR_NONE);

	glutMainLoop();

	delete(mouse);
	delete(cursor);
	delete(tf_world);
	delete(tf_cursor);
	delete(board);

	return EXIT_SUCCESS;
}
