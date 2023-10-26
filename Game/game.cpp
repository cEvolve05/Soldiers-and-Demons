#include "include.h"

activity* activityManager::currentActivity = NULL;
bool game::running = 0;

game::game()
{
	this->running = 1;
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
	initgraph(500, 500, EX_SHOWCONSOLE);
	activityManager::setActivity(new MenuActivity);
	return;
}

void game::end()
{
	closegraph();
	return;
}


activityManager::activityManager()
{
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

MenuActivity::MenuActivity()
{
}

MenuActivity::~MenuActivity()
{
}

void MenuActivity::lifeCycle()
{
	//code for Menu
	while (game::getRunningStatus() && !exitActivity)
	{
		
	}
	return;
}

GamingActivity::GamingActivity()
{
	LuserLastInput = 0;
	RuserLastInput = 0;
	LinputRequireProcess = 0;
	RinputRequireProcess = 0;
	m = { 0 };
}

GamingActivity::~GamingActivity()
{
}

void GamingActivity::lifeCycle()
{
	//loop inside
	//code for Gaming
	while (game::getRunningStatus()&&!exitActivity)
	{
		inputProcess();
		process();
		render();
	}
	return;
}

void GamingActivity::inputProcess()
{

	//flushmessage(EX_MOUSE | EX_CHAR);
	//Input Process
	while (peekmessage(&m, EX_MOUSE | EX_KEY))
	{
		switch (m.message)
		{
		case WM_MOUSEMOVE:
			putpixel(m.x, m.y, RED);
			break;

		case WM_KEYDOWN:
			//may can be optimized
			if (m.vkcode == VK_ESCAPE)
			{
				game::setRunningStatus(0);
				return;
			}
			if ((m.vkcode == 'W' || m.vkcode == 'S' || m.vkcode == 'A' || m.vkcode == 'D') && m.prevdown == 0)
			{
				LuserLastInput = m.vkcode;
				LinputRequireProcess = true;
			}
			if ((m.vkcode == VK_LEFT || m.vkcode == VK_UP || m.vkcode == VK_DOWN || m.vkcode == VK_RIGHT) && m.prevdown == 0)
			{
				RuserLastInput = m.vkcode;
				RinputRequireProcess = true;
			}
			break;

		default:
			break;
		}
	}
	return;
}

void GamingActivity::process()
{
	if (LinputRequireProcess)
	{
		//Process L role move, touch
		LinputRequireProcess = false;
	}
	
	if (RinputRequireProcess)
	{
		//Process R role move, touch
		RinputRequireProcess = false;
	}
	return;
}

void GamingActivity::render()
{
	//testRole.render();
	return;
}

RuleIntroActivity::RuleIntroActivity()
{
}

RuleIntroActivity::~RuleIntroActivity()
{
}

void RuleIntroActivity::lifeCycle()
{
	//loop inside
	//code for RuleIntro
	while (game::getRunningStatus() && !exitActivity)
	{

	}
	return;
}

BackgroundIntroActivity::BackgroundIntroActivity()
{
}

BackgroundIntroActivity::~BackgroundIntroActivity()
{
}

void BackgroundIntroActivity::lifeCycle()
{
	//loop inside
	//code for BackgroundIntro
	while (game::getRunningStatus() && !exitActivity)
	{

	}
	return;
}

KeyBindingIntroActivity::KeyBindingIntroActivity()
{
}

KeyBindingIntroActivity::~KeyBindingIntroActivity()
{
}

void KeyBindingIntroActivity::lifeCycle()
{
	//loop inside
	//code for KeyBindingIntro
	while (game::getRunningStatus() && !exitActivity)
	{

	}
	return;
}