#include <stdio.h>
#include <GL/freeglut.h>
#include "screenutil.h"

void printText(bool setPosition, GLint x, GLint y, char const *s, GLubyte red, GLubyte green, GLubyte blue)
{
	glColor3ub(red, green, blue);

	if (setPosition)
	{
		glRasterPos2i(x, y);
	}

	for (size_t i = 0; s[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	}
}

void printInt(bool setPosition, GLint x, GLint y, int i, GLubyte red, GLubyte green, GLubyte blue)
{
	char buffer[20];
	snprintf(buffer, 20, "%d", i);
	printText(setPosition, x, y, buffer, red, green, blue);
}

void printFloat(bool setPosition, GLint x, GLint y, float f, GLubyte red, GLubyte green, GLubyte blue)
{
	char buffer[20];
	snprintf(buffer, 20, "%f", f);
	printText(setPosition, x, y, buffer, red, green, blue);
}

void textResetBottomLeft()
{
	glRasterPos2i(rasterLeft, rasterBottom);
}

void textYellow()
{
	glColor3ub(192, 192, 0);
}

void textOut(char const *s)
{
	for (size_t i = 0; s[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	}
}

void textOutInt(int i)
{
	char buffer[20];
	snprintf(buffer, 20, "%d", i);
	textOut(buffer);
}

void textOutFloat(float f)
{
	char buffer[20];
	snprintf(buffer, 20, "%f", f);
	textOut(buffer);
}
