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

int mouse_x;
int mouse_y;
GLfloat mouse_world_x;
GLfloat mouse_world_y;
int mouseWheelDirection;

bool keyState[256];
GLfloat angle = 0.0f;

GLfloat scale = initialScale;
GLfloat translate_x = (-BOARD_WIDTH / 2.0f);
GLfloat translate_y = (-BOARD_HEIGHT / 2.0f);


Board* board;
Transform* tf_world;
Transform* tf_cursor;

// screen to board cell
void getBoardPos(int x, int y, GLfloat scale, GLfloat trans_x, GLfloat trans_y, GLfloat *bx, GLfloat *by)
{
	GLfloat mx, my;
	screenToWorld(mouse_x, mouse_y, scale, translate_x, translate_y, &mx, &my);
	*bx = floorf(mx);
	*by = floorf(my);
}

void drawCursor()
{
	GLfloat newScale = 1.0f;
	GLfloat cursorSize = 0.2f;

	glLoadIdentity();
	glScalef(newScale, newScale, newScale);

	GLfloat mx, my;
	screenToWorld(mouse_x, mouse_y, newScale, 0, 0, &mx, &my);

	glTranslatef(mx, my, 0);

	glColor3ub(32, 192, 0);
	glBegin(GL_QUADS);

	glVertex2f(0, 0);
	glVertex2f(cursorSize, -cursorSize * 2.0f);
	glVertex2f(cursorSize, -cursorSize);
	glVertex2f(cursorSize * 2.0f, -cursorSize);

	glEnd();
}

bool isPointInRect(GLfloat px, GLfloat py, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom)
{
	return px >= left && px <= right && py >= bottom && py <= top;
}

void drawCell(int cx, int cy)
{
	Cell *cell = board->getcell(cx, cy);

	GLubyte cols[] = { 0, 0, 0 };
	getColorByCode(cell->color, cols, cell->state);
	glColor3ubv(cols);

	glVertex2f(cx, cy);
	glVertex2f(cx + 1.0f, cy);
	glVertex2f(cx + 1.0f, cy + 1.0f);
	glVertex2f(cx, cy + 1.0f);
}

void display()
{
	if (keyState['a'])
	{
		translate_x += translateIncrement;
	}
	if (keyState['d'])
	{
		translate_x -= translateIncrement;
	}
	if (keyState['w'])
	{
		translate_y -= translateIncrement;
	}
	if (keyState['s'])
	{
		translate_y += translateIncrement;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	
	glScalef(scale, scale, scale);
	glTranslatef(translate_x, translate_y, 0);
	glBegin(GL_QUADS);

	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			drawCell(x, y);
		}
	}
	glEnd();

	GLfloat bx, by;
	getBoardPos(mouse_x, mouse_y, scale, translate_x, translate_y, &bx, &by);

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

	drawCursor();

	glPopMatrix();

	//GLfloat s = (2.0f * orthoSize) / scale;
	//printFloat(true, rasterLeft, 0, s, 192, 192, 192);

	printInt(true, rasterLeft, rasterBottom, mouse_x, 128, 128, 0);
	printText(false, 0, 0, ", ", 128, 128, 0);
	printInt(false, 0, 0, mouse_y, 128, 128, 0);

	printText(false, 0, 0, " - ", 128, 128, 0);
	printFloat(false, 0, 0, scale, 128, 128, 0);

	printText(false, 0, 0, " - ", 128, 128, 0);
	printFloat(false, 0, 0, translate_x, 128, 128, 0);


	glutSwapBuffers();
	glutPostRedisplay();
}

void saveMousePosition(int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}

#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4

void processMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		GLfloat bx, by;
		getBoardPos(mouse_x, mouse_y, scale, translate_x, translate_y, &bx, &by);
		Cell *cell = board->getcell(bx, by);
		cell->state = (cell->state == 0) ? 1 : 0;
	}

	// Used for wheels, has to be up
	if (state == GLUT_UP)
	{
		if (button == GLUT_WHEEL_UP)
		{
			mouseWheelDirection = 1;
			scale += scaleIncrement;
		}
		else if (button == GLUT_WHEEL_DOWN)
		{
			mouseWheelDirection = -1;
			if (scale > 0)
			{
				scale -= scaleIncrement;
			}
		}
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

	delete(tf_world);
	delete(tf_cursor);
	delete(board);

	return EXIT_SUCCESS;
}
