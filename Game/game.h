#pragma once
#include <graphics.h>
#include <iostream>
#include <winuser.h>

#include "resource.h"
#include "object.h"
#include "activityManager.h"

class game
{
public:
	game();
	~game();
	void entry();

	static bool getRunningStatus();
	static void setRunningStatus(bool status);

private:
	static bool running;

	void init();
	void end();
};

game::game()
{
	this->running = 1;
}

game::~game()
{
}

inline void game::entry()
{
	init();
	activityManager::showActivity();
	end();
}

inline bool game::getRunningStatus()
{
	return running;
}

inline void game::setRunningStatus(bool status)
{
	running = status;
}

inline void game::init()
{
	initgraph(500, 500, EX_SHOWCONSOLE);
	activityManager::setActivity(new MenuActivity);
}


inline void game::end()
{
	closegraph();
	return;
}