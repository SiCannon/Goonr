#pragma once

class Mouse;

typedef void (*MouseEvent)(Mouse *mouse);

class Mouse
{
public:
	Mouse();
	int x;
	int y;
	void set(int x, int y);
	void process(int button, int state, int x, int y);
	MouseEvent onMouseLeftClick;
	MouseEvent onMouseWheelUp;
	MouseEvent onMouseWheelDown;
};
