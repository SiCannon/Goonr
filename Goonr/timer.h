#pragma once

class Timer
{
	long lastTicks;
public:
	long elapsedTicks;
	void tick();
};
