#pragma once

#include <GL/freeglut.h>

void printText(bool setPosition, GLint x, GLint y, char const *s, GLubyte red, GLubyte green, GLubyte blue);
void printInt(bool setPosition, GLint x, GLint y, int i, GLubyte red, GLubyte green, GLubyte blue);
void printFloat(bool setPosition, GLint x, GLint y, float f, GLubyte red, GLubyte green, GLubyte blue);

void textResetBottomLeft();
void textYellow();
void textOut(char const *s);
void textOutInt(int i);
void textOutFloat(float f);

