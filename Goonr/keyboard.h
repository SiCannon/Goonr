#pragma once

#include "transform.h"

extern bool keyState[256];

void getKeyboardDown(unsigned char key, int x, int y);
void getKeyboardUp(unsigned char key, int x, int y);
void handleInput(Transform *worldTransform);

