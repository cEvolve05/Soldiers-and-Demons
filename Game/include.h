#pragma once
#include <graphics.h>
#include <iostream>
#include <winuser.h>

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

// object include role, words, efforts.
class object
{
public:
	object();
	object(POINT location, LPCTSTR pResType, LPCTSTR pResName);
	object(POINT location, LPCTSTR pImgFile);
	~object();

	enum XorY
	{
		X,
		Y
	};

	void setLocation(POINT location);
	LONG getLocation(XorY choose) const;
	void shiftLocation(POINT shiftValue);

	// get img from resource
	void setImg(LPCTSTR pResType, LPCTSTR pResName);
	void setImg(LPCTSTR pImgFile);

	virtual void render();

protected:
	// left-top point
	POINT objectLocation;
	IMAGE objectImg;

	//0 as lowest layer,render first;the bigger, the later
	//bg=0,board=1,HUD=1,word=2,effortL=3,player=4,effortH=5
	//int renderLevel;
};

class role final: public object
{
public:
	/*struct roleData
	{
		int attack; //attack
		int magicAttack; //magic attack
		int healthPoints; //health points
		int recovery;
		int speed;
	}roleOriginData, roleCurrentData;*/

	role();
	//role(POINT location, LPCTSTR pResType, LPCTSTR pResName, roleData INdata);
	role(POINT location, LPCTSTR pResType, LPCTSTR pResName);

private:

};

class board final: protected object
{
public:
	//size{4,5} meaning 4*5 board
	void setBoardSize(POINT size);

	//meaning blank size
	void setGridSize(POINT size);
	void render() override;
private:
	POINT boardSize;
	POINT gridSize;
	POINT boardLocation;
};

class activity
{
public:
	activity();
	~activity();
	virtual void lifeCycle()=0;
	void button(int x1, int y1, int x2, int y2, wchar_t arr[]);
protected:
	bool exitActivity;
};

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

class StartActivity final : public activity
{
public:
	void lifeCycle() override;

private:

};

class PlayRuleIntroActivity final : public activity
{
public:
	void lifeCycle() override;

private:

};

class TextRuleIntroActivity final : public activity
{
public:
	void lifeCycle() override;

private:

};

class MenuActivity final: public activity
{
public:
	void lifeCycle() override;

private:

};

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

	role L;
	role R;

	void inputProcess();
	void process();
	void render();

};

class RuleIntroActivity final : public activity
{
public:
	void lifeCycle() override;

private:

};

class BackgroundIntroActivity final : public activity
{
public:
	void lifeCycle() override;

private:

};

class KeyBindingIntroActivity final : public activity
{
public:
	void lifeCycle() override;

private:

};
