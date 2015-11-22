#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <string>

using namespace std;

#define initialScale 5
#define scaleIncrement 0.05f
#define orthoSize 10.0f
#define intialWindowWidth 800
#define intialWindowHeight 600
#define translateIncrement 0.1f

int mouse_x;
int mouse_y;
int mouseWheelDirection;
int windowWidth;
int windowHeight;

unsigned char keyState[256];

GLfloat scale = initialScale;
GLfloat translate_x = 0;
GLfloat translate_y = 0;

int rasterLeft = 0;
int rasterBottom = 0;

void printText(bool setPosition, GLint x, GLint y, std::string s, GLubyte red, GLubyte green, GLubyte blue)
{
	glColor3ub(red, green, blue);

	if (setPosition)
	{
		glRasterPos2i(x, y);
	}

	for (size_t i = 0; i < s.size(); ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	}
}

void printInt(bool setPosition, GLint x, GLint y, int i, GLubyte red, GLubyte green, GLubyte blue)
{
	printText(setPosition, x, y, std::to_string(i), red, green, blue);
}

void printInfo()
{
	//printInt(
}

void convertPos(int x, int y, GLfloat scale, GLfloat *wx, GLfloat *wy)
{
	GLfloat aspect_ratio = (GLfloat)windowWidth / (GLfloat)windowHeight;
	GLfloat orthoHeight = orthoSize / scale;
	GLfloat orthoWidth = orthoHeight * aspect_ratio;

	*wx = 2.0f * orthoWidth * (GLfloat)x / (GLfloat)windowWidth - orthoWidth;
	*wy = orthoHeight - 2.0f * orthoHeight * (GLfloat)y / (GLfloat)windowHeight;
}

void drawCursor()
{
	GLfloat newScale = 1.0f;

	glLoadIdentity();
	glScalef(newScale, newScale, newScale);

	/*GLfloat aspect_ratio = (GLfloat)windowWidth / (GLfloat)windowHeight;
	GLfloat orthoHeight = orthoSize / newScale;
	GLfloat orthoWidth = orthoHeight * aspect_ratio;

	GLfloat mx = 2.0f * orthoWidth * (GLfloat)mouse_x / (GLfloat)windowWidth - orthoWidth;
	GLfloat my = orthoHeight - 2.0f * orthoHeight * (GLfloat)mouse_y / (GLfloat)windowHeight;*/

	GLfloat mx, my;
	convertPos(mouse_x, mouse_y, newScale, &mx, &my);

	glColor3ub(32, 192, 0);
	glBegin(GL_QUADS);
	glVertex2f(mx, my);
	glVertex2f(mx + 0.1, my - 0.2);
	glVertex2f(mx + 0.1, my - 0.1);
	glVertex2f(mx + 0.2, my - 0.1);
	glEnd();
}

bool isPointInRect(GLfloat px, GLfloat py, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom)
{
	return px >= left && px <= right && py >= top && py <= bottom;
}

void display() {

	GLfloat mx, my;
	convertPos(mouse_x, mouse_y, scale, &mx, &my);
	bool isInside = isPointInRect(mx, my, -1, 1, -1, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (isInside)
	{
		glColor3ub(255, 192, 0);
	}
	else
	{
		glColor3ub(192, 64, 0);
	}
	glPushMatrix();
	
	glTranslatef(translate_x, translate_y, 0);
	glScalef(scale, scale, scale);
	glBegin(GL_QUADS);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, 1);
	glVertex2f(-1, 1);
	glEnd();

	drawCursor();

	glPopMatrix();

	GLfloat s = (2.0f * orthoSize) / scale;
	printText(true, rasterLeft, 0, std::to_string(s), 192, 192, 192);



	/*printText(0, 0, "pos: ", 128, 128, 0);
	printText(4, 0, std::to_string(mouse_x), 128, 128, 0);
	printText(8, 0, std::to_string(mouse_y), 128, 128, 0);
	printText(4, 1, std::to_string(mouseWheelDirection), 128, 128, 0);

	for (int i = -5; i <= 5; i++)
	{
		printText(-5, i, std::to_string(i), 128, 128, 0);
	}*/

	/*for (int x = -10; x <= 10; x++)
	{
		for (int y = -10; y <= 10; y++)
		{
			printText(x, y, std::to_string(x), 128, 128, 0);
		}
	}*/

	printText(true, rasterLeft, rasterBottom, std::to_string(mouse_x), 128, 128, 0);
	printText(false, 0, 0, ", ", 128, 128, 0);
	printText(false, 0, 0, std::to_string(mouse_y), 128, 128, 0);

	printText(false, 0, 0, " - ", 128, 128, 0);
	printText(false, 0, 0, std::to_string(scale), 128, 128, 0);

	glutSwapBuffers();
	glutPostRedisplay();
}

/*void reCalcMouseScaling()
{
	mouseScale = ((2.0f * orthoSize) / scale);
}*/

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
	// Used for wheels, has to be up
	if (state == GLUT_UP)
	{
		if (button == GLUT_WHEEL_UP)
		{
			mouseWheelDirection = 1;
			scale += scaleIncrement;
			//reCalcMouseScaling();
		}
		else if (button == GLUT_WHEEL_DOWN)
		{
			mouseWheelDirection = -1;
			if (scale > 0)
			{
				scale -= scaleIncrement;
				//reCalcMouseScaling();
			}
		}
	}
}

void getKeyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		translate_x -= translateIncrement;
	}
	else if (key == 'd')
	{
		translate_x += translateIncrement;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(intialWindowWidth, intialWindowHeight);
	glutCreateWindow("Text");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(saveMousePosition);
	glutMouseFunc(processMouse);
	glutKeyboardFunc(getKeyboard);
	glutMainLoop();
	return EXIT_SUCCESS;
}