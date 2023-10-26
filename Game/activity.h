#pragma once
#include <graphics.h>
#include "game.h"
#include "activityManager.h"
#include "object.h"

class activity
{
public:
	virtual void lifeCycle()=0;
protected:
	bool exitActivity;
};



class MenuActivity final: public activity
{
public:
	MenuActivity();
	~MenuActivity();
	void lifeCycle() override;

private:

};

MenuActivity::MenuActivity()
{
}

MenuActivity::~MenuActivity()
{
}

inline void MenuActivity::lifeCycle()
{
	//code for Menu
	while (game::getRunningStatus() && !exitActivity)
	{
		
	}
	return;
}

class GamingActivity final : public activity
{
public:
	GamingActivity();
	~GamingActivity();
	void lifeCycle() override;

private:
	ExMessage m;
	char LuserLastInput, RuserLastInput;
	bool LinputRequireProcess, RinputRequireProcess;

	role L(,,),
		R(,,);

	void inputProcess();
	void process();
	void render();

private:

};

GamingActivity::GamingActivity()
{
	LuserLastInput = 0;
	RuserLastInput = 0;
	LinputRequireProcess = 0;
	RinputRequireProcess = 0;
}

GamingActivity::~GamingActivity()
{
}

inline void GamingActivity::lifeCycle()
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

inline void GamingActivity::inputProcess()
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
}

inline void GamingActivity::process()
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
}

inline void GamingActivity::render()
{
	//testRole.render();
}

class RuleIntroActivity final : public activity
{
public:
	RuleIntroActivity();
	~RuleIntroActivity();
	void lifeCycle() override;

private:

};

RuleIntroActivity::RuleIntroActivity()
{
}

RuleIntroActivity::~RuleIntroActivity()
{
}

inline void RuleIntroActivity::lifeCycle()
{
	//loop inside
	//code for RuleIntro
	while (game::getRunningStatus() && !exitActivity)
	{

	}
	return;
}

class BackgroundIntroActivity final : public activity
{
public:
	BackgroundIntroActivity();
	~BackgroundIntroActivity();
	void lifeCycle() override;

private:

};

BackgroundIntroActivity::BackgroundIntroActivity()
{
}

BackgroundIntroActivity::~BackgroundIntroActivity()
{
}

inline void BackgroundIntroActivity::lifeCycle()
{
	//loop inside
	//code for BackgroundIntro
	while (game::getRunningStatus() && !exitActivity)
	{

	}
	return;
}

class KeyBindingIntroActivity final : public activity
{
public:
	KeyBindingIntroActivity();
	~KeyBindingIntroActivity();
	void lifeCycle() override;

private:

};

KeyBindingIntroActivity::KeyBindingIntroActivity()
{
}

KeyBindingIntroActivity::~KeyBindingIntroActivity()
{
}

inline void KeyBindingIntroActivity::lifeCycle()
{
	//loop inside
	//code for KeyBindingIntro
	while (game::getRunningStatus() && !exitActivity)
	{

	}
	return;
}