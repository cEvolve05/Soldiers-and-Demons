#include <graphics.h>
#include <iostream>
#include <winuser.h>
#include <winnt.h>
#include <conio.h>
#include <vector>

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
		Item,
		Action,
		Special,
		COUNT //Last one
	};

	word(std::wstring text, int length = 0, wordType type = word::Subject);
	//void render(POINT from, POINT to);

	std::wstring text;
	int length;
	wordType type;
protected:

};

word::word(std::wstring text, int length, wordType type)
{
	text = text;
	if (length == 0)
	{
		length = text.size();
	}
	else
	{
		length = length;
	}
	type = type;
}


int main()
{
	//word ** data = new word * [5]
	//	{
	//		//Subject
	//		new word[2]
	//		{
	//			{L"勇者",2,word::Subject},
	//			{L"魔王",2,word::Subject},
	//		},

	//		//Verb
	//			new word[2]
	//		{
	//			{L"使用",2,word::Verb},
	//			//{L"进行",0,word::Verb},
	//			//{L"释放",0,word::Verb},
	//			{L"使出",2,word::Verb},
	//		},

	//		//Object
	//			new word[2]
	//		{
	//			{L"食物",2,word::Object},
	//			{L"药剂",2,word::Object},
	//		},

	//		//Action
	//			new word[3]
	//		{
	//			{L"攻击",2,word::Action},
	//			{L"强力攻击",4,word::Action},
	//			{L"防御",2,word::Action},
	//		},

	//		//Special
	//			new word[4]
	//		{
	//			{L"清空文本框",5,word::Special},
	//			{L"移除词块",4,word::Special},
	//			{L"生成词块",4,word::Special},
	//			{L"禁用棋盘",4,word::Special},
	//		},
	//	};
	{
		struct possibilityBlock
		{
			word word;
			unsigned short int possibility;
		};
		std::vector<std::vector<possibilityBlock>> data;

		{
			//Subject
			data.push_back
			({
					{{L"勇者",2,word::Subject},1},
					{{L"魔王",2,word::Subject},1},
			});

			//Verb
			data.push_back
			({
					{{L"使用",2,word::Verb},1},
					//{{L"进行",0,word::Verb},1},
					//{{L"释放",0,word::Verb},1},
					{{L"使出",2,word::Verb},2},
			});

			//Object
			data.push_back
			({
					{{L"食物",2,word::Item},2},
					{{L"药剂",2,word::Item},1},
			});

			//Action
			data.push_back
			({
					{{L"攻击",2,word::Action},2},
					{{L"强力攻击",4,word::Action},1},
					//{{L"防御",2,word::Action},1},
			});

			//Special
			data.push_back
			({
					{{L"清空文本框",5,word::Special},1},
					{{L"移除词块",4,word::Special},1},
					{{L"生成词块",4,word::Special},1},
					{{L"禁用棋盘",4,word::Special},1},
			});
		}
		int* size = new int[word::COUNT];
		for (int i = 0; i < word::wordType::COUNT; i++)
		{
			size[i] = data[i].size();//BUG
			cout << size[i] << endl;
		}
	}
	_getch();

	return 0;
}