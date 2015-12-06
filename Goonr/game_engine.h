#pragma once

class GameEngine
{
	Board* board;
	Transform* tf_world;
	Cursor *cursor;
	Mouse *mouse;
	Highlight *highlight;
public:
	GameEngine();
};
