#pragma once
#include <graphics.h>
#include <iostream>
#include <winuser.h>
#include <queue>

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
//class object
//{
//public:
//	object();
//	~object();
//
//	enum XorY
//	{
//		X,
//		Y
//	};
//
//	void setLocation(POINT location);
//	LONG getLocation(XorY choose) const;
//	void shiftLocation(POINT shiftValue);
//
//	// get img from resource
//	void setImg(LPCTSTR pResType, LPCTSTR pResName);
//	void setImg(LPCTSTR pImgFile);
//
//	virtual void render();
//
//protected:
//	// left-top point
//	POINT objectLocation;
//	IMAGE objectImg;
//
//	POINT size;
//
//	//0 as lowest layer,render first;the bigger, the later
//	//bg=0,board=1,HUD=1,word=2,effortL=3,player=4,effortH=5
//	//int renderLevel;
//};

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

class RuleIntroActivity final : public activity
{
public:
	void lifeCycle() override;
};

class BackgroundIntroActivity final : public activity
{
public:
	void lifeCycle() override;
};

class KeyBindingIntroActivity final : public activity
{
public:
	void lifeCycle() override;
};

class word
{
public:
	enum wordType
	{
		Subject,
		Verb,
		Object,
		Action,
		Special,
	};

	word(std::wstring text,int length=0, wordType type);
	void render(POINT from, POINT to);

	std::wstring text;
	int length;
	wordType type;
protected:

};

//class verbBlock : public word TODO

//class nounBlock : public word TODO


class role
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
	void setLocation(POINT location);
	void setImg(LPCTSTR pResType, LPCTSTR pResName, POINT size);
	void setImg(LPCTSTR pImgFile, POINT size);

	void render();

	//role(POINT location, LPCTSTR pResType, LPCTSTR pResName, roleData INdata);
	//role(POINT location, LPCTSTR pResType, LPCTSTR pResName);

	int health;
private:
	POINT location;
	IMAGE img;
};

class textBox
{
	friend class wordProcess;
public:
	textBox();
	~textBox();

	void addWord(word* INword);
	void empty();

	void setLocation(POINT from, POINT to);

	void render();
private:
	std::vector<word*> words;
	POINT from, to;
};

class board
{
	friend class wordProcess;
public:
	board();
	~board();

	role* player;

	//render from from to to
	void setBoardLocation(POINT from, POINT to);
	//size{4,5} meaning 4*5 board
	void setGrid(POINT grid);
	void init(LPCTSTR pImgFile);

	void setPlayerLocation(POINT location);
	void getGridLocation(POINT& from, POINT& to, POINT gridLocationFrom, POINT gridLocationTo={-1,-1}) const;
	POINT getGridLocation(POINT location);
	void addWord(word* word, POINT wordHeadLocation);
	word* getWord(POINT location);
	void delWord(POINT location);

	void render() const;

	POINT playerLocation;//grid location
private:
	struct wordBlock
	{
		word* word;
		POINT headLocation;
	};
	POINT from, to;//for location
	POINT grid;//for board grid
	std::vector<wordBlock*> wordVault;//������е�wordVault��ָ�������
	wordBlock*** WordInBoard;//һ����Ÿ������ӵģ�ָ��������Ӷ�Ӧ��wordVault��ָ�룩�Ķ�ά����
	
	//Auto generate:
	DWORD lineWidth;
	POINT gridBlankSize;
};

class wordProcess
{
public:
	wordProcess();
	~wordProcess();

	void generateWord(board* targetBoard);
	bool applySentence(textBox* targetTextBox);

private:
	word** data;
	int size[5];
};

class GamingActivity final : public activity
{
public:
	void lifeCycle() override;

private:
	ExMessage m;
	std::queue<int> input;

	board* L;
	textBox* Lbox;

	void init();
	void end();

	void inputFilter();
	void process();
	void render();
};
