#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <string>

using namespace std;

#define initialScale 5
#define scaleIncrement 0.05
#define orthoSize 10
#define intialWindowWidth 800
#define intialWindowHeight 600

int mouse_x;
int mouse_y;
int mouseWheelDirection;

GLfloat scale = initialScale;

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
	printText(setPosition, 4, 0, std::to_string(i), red, green, blue);
}

void printInfo()
{
	//printInt(
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3ub(192, 64, 0);
	glPushMatrix();
	
	glScalef(scale, scale, scale);
	glBegin(GL_QUADS);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, 1);
	glVertex2f(-1, 1);
	glEnd();
	glPopMatrix();

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

void reshape(int w, int h)
{
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
	glutMainLoop();
	return EXIT_SUCCESS;
}