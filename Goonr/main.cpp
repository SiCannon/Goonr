#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <string>

using namespace std;

int mouse_x;
int mouse_y;
int mouseWheelDirection;
GLfloat scale = 1;

void printText(GLint x, GLint y, std::string s, GLubyte red, GLubyte green, GLubyte blue)
{
	glColor3ub(red, green, blue);
	glRasterPos2i(x, y);

	for (size_t i = 0; i < s.size(); ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	}
}

void printInt(GLint x, GLint y, int i, GLubyte red, GLubyte green, GLubyte blue)
{
	printText(4, 0, std::to_string(i), red, green, blue);
}

void printInfo()
{
	//printInt(
}

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
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

	printText(0, 0, "pos: ", 128, 128, 0);
	printText(4, 0, std::to_string(mouse_x), 128, 128, 0);
	printText(8, 0, std::to_string(mouse_y), 128, 128, 0);
	printText(4, 1, std::to_string(mouseWheelDirection), 128, 128, 0);

	for (int i = -5; i <= 5; i++)
	{
		printText(-5, i, std::to_string(i), 128, 128, 0);
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double aspect_ratio = (double)w / (double)h;
	glOrtho(-10 * aspect_ratio, 10 * aspect_ratio, -10, 10, -1, 1);
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
			scale += 0.1;
		}
		else if (button == GLUT_WHEEL_DOWN)
		{
			mouseWheelDirection = -1;
			if (scale > 0)
			{
				scale -= 0.1;
			}
		}
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Text");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(saveMousePosition);
	glutMouseFunc(processMouse);
	glutMainLoop();
	return EXIT_SUCCESS;
}