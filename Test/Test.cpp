#include <graphics.h>
#include <iostream>
#include <winuser.h>
#include <winnt.h>
#include <conio.h>

#include <wchar.h>//Debug

#include "resource.h"

#define DEBUG

#pragma execution_character_set("utf-8")

using namespace std;

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

	word(std::wstring text, int length = 0, wordType type=word::Subject);
	//void render(POINT from, POINT to);

	std::wstring text;
	int length;
	wordType type;
protected:

};

word::word(std::wstring text, int length, wordType type)
{
	this->text = text;
	if (length == 0)
	{
		this->length = text.size();
	}
	else
	{
		this->length = length;
	}
	this->type = type;
}


int main()
{
	word ** data = new word * [5]
		{
			//Subject
			new word[2]
			{
				{L"勇者",2,word::Subject},
				{L"魔王",2,word::Subject},
			},

			//Verb
				new word[2]
			{
				{L"使用",2,word::Verb},
				//{L"进行",0,word::Verb},
				//{L"释放",0,word::Verb},
				{L"使出",2,word::Verb},
			},

			//Object
				new word[2]
			{
				{L"食物",2,word::Object},
				{L"药剂",2,word::Object},
			},

			//Action
				new word[3]
			{
				{L"攻击",2,word::Action},
				{L"强力攻击",4,word::Action},
				{L"防御",2,word::Action},
			},

			//Special
				new word[4]
			{
				{L"清空文本框",5,word::Special},
				{L"移除词块",4,word::Special},
				{L"生成词块",4,word::Special},
				{L"禁用棋盘",4,word::Special},
			},
		};
	wcout.imbue(locale("zh-CN"));
	wcout << data[2][1].text;
	wcout << L"dwdwd";
	cout << "a";

	_getch();
	
	return 0;
}