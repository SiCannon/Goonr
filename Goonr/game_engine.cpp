#include "game_engine.h"

void GameEngine::GameEngine()
{
	board = new Board();
	tf_world = new Transform();
	cursor = new Cursor();
	mouse = new Mouse();
	highlight = new Highlight();
}
