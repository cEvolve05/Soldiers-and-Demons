#pragma once
#include <graphics.h>

#include "activity.h"
#include "game.h"

//activity satrter
class activityManager
{
public:
	activityManager();
	~activityManager();

	static bool exitActivity;

	static void setActivity(activity* a);
	static void showActivity();

private:
	static activity* currentActivity;
};

activityManager::activityManager()
{
}

activityManager::~activityManager()
{
}

inline void activityManager::setActivity(activity* a)
{
	currentActivity = a;
	return;
}

inline void activityManager::showActivity()
{
	while (game::getRunningStatus())
	{
		currentActivity->lifeCycle();
	}
	return;
}

