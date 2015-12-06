#pragma once

#include <GL/freeglut.h>
#include "mouse.h"
#include "textutils.h"

extern GLfloat rasterLeft;
extern GLfloat rasterBottom;

void reshape(int w, int h);
void screenToWorld(int x, int y, GLfloat scale, GLfloat trans_x, GLfloat trans_y, GLfloat *wx, GLfloat *wy);
void getBoardPos(Mouse *mouse, GLfloat scale, GLfloat trans_x, GLfloat trans_y, GLfloat *bx, GLfloat *by);
