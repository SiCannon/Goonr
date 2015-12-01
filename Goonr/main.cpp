#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#include "textutils.h"
#include "CellColors.h"
#include "board.h"

#define initialScale 0.5
#define scaleIncrement 0.05f
#define orthoSize 10.0f
#define intialWindowWidth 800
#define intialWindowHeight 600
#define translateIncrement 0.1f

int mouse_x;
int mouse_y;
GLfloat mouse_world_x;
GLfloat mouse_world_y;
int mouseWheelDirection;
int windowWidth;
int windowHeight;

bool keyState[256];

GLfloat scale = initialScale;
GLfloat translate_x = (-BOARD_WIDTH / 2.0f);
GLfloat translate_y = (-BOARD_HEIGHT / 2.0f);

GLfloat rasterLeft = 0;
GLfloat rasterBottom = 0;

Board* board;

void convertPos(int x, int y, GLfloat scale, GLfloat trans_x, GLfloat trans_y, GLfloat *wx, GLfloat *wy)
{
	GLfloat aspect_ratio = (GLfloat)windowWidth / (GLfloat)windowHeight;
	GLfloat orthoHeight = orthoSize / scale;
	GLfloat orthoWidth = orthoHeight * aspect_ratio;

	*wx = 2.0f * orthoWidth * (GLfloat)x / (GLfloat)windowWidth - orthoWidth - trans_x;
	*wy = orthoHeight - 2.0f * orthoHeight * (GLfloat)y / (GLfloat)windowHeight - trans_y; // shouldn't this be  + trans_y ??
}

void getBoardPos(int x, int y, GLfloat scale, GLfloat trans_x, GLfloat trans_y, GLfloat *bx, GLfloat *by)
{
	GLfloat mx, my;
	convertPos(mouse_x, mouse_y, scale, translate_x, translate_y, &mx, &my);
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
	convertPos(mouse_x, mouse_y, newScale, 0, 0, &mx, &my);

	glColor3ub(32, 192, 0);
	glBegin(GL_QUADS);
	glVertex2f(mx, my);
	glVertex2f(mx + cursorSize, my - cursorSize * 2.0f);
	glVertex2f(mx + cursorSize, my - cursorSize);
	glVertex2f(mx + cursorSize * 2.0f, my - cursorSize);
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

	drawCursor();

	glPopMatrix();

	GLfloat s = (2.0f * orthoSize) / scale;
	printFloat(true, rasterLeft, 0, s, 192, 192, 192);

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

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glEnable(GL_MULTISAMPLE);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(intialWindowWidth, intialWindowHeight);
	glutCreateWindow("Text");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(saveMousePosition);
	glutMotionFunc(saveMousePosition);
	glutMouseFunc(processMouse);
	glutKeyboardFunc(getKeyboardDown);
	glutKeyboardUpFunc(getKeyboardUp);
	glutSetCursor(GLUT_CURSOR_NONE);

	glutMainLoop();

	delete(board);

	return EXIT_SUCCESS;
}
