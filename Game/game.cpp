#include "include.h"
#include <graphics.h>

activity* activityManager::currentActivity = NULL;
bool game::running = 0;

game::game()
{
	this->running = 1;
	//std::cout << typeid(this).name() << std::endl;
}

game::~game()
{
}

bool game::getRunningStatus()
{
	return running;
}

void game::setRunningStatus(bool status)
{
	running = status;
	return;
}

void game::entry()
{
	init();
	activityManager::showActivity();
	end();
	return;
}

void game::init()
{
	initgraph(1024, 615, EX_SHOWCONSOLE | EW_NOCLOSE);
	activityManager::setActivity(new StartActivity);
	return;
}

void game::end()
{
	closegraph();
	return;
}


activityManager::activityManager()
{
	//std::cout << typeid(this).name() << std::endl;
}

activityManager::~activityManager()
{
}

void activityManager::showActivity()
{
	while (game::getRunningStatus())
	{
		currentActivity->lifeCycle();
	}
	return;
}

void activityManager::setActivity(activity* a)
{
	currentActivity = a;
	return;
}
