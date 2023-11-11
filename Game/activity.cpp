#include "include.h"


activity::activity()
{
	this->exitActivity = 0;
	std::cout << typeid(this).name() << std::endl;
}

activity::~activity()
{
}

void activity::button(int x1, int y1, int x2, int y2, wchar_t arr[])
{
	setfillcolor(RGB(240, 155, 89));
	fillrectangle(x1, y1, x2, y2);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(40, 0, L"����");
	int w = (x2 - x1 - textwidth(arr)) / 2;
	int h = (y2 - y1 - textheight(arr)) / 2;
	outtextxy(x1 + w, y1 + h, arr);
	setfillcolor(WHITE);
}


void StartActivity::lifeCycle()
{
	//code for Start
	//initgraph(1024, 615, EX_SHOWCONSOLE);
	IMAGE background;
	loadimage(&background, L"./Resource/��ʼ����.png", 0, 0);
	putimage(0, 0, &background);
	ExMessage msg;
	while (game::getRunningStatus() && !exitActivity)
	{
		//std::cout << peekmessage(&msg, EX_MOUSE, false);
		if (peekmessage(&msg, EX_MOUSE))//�������Ϣ�ͷ����棬û�з��ؼ�
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN://�������Ҽ�,����������
				//std::cout << "WM_LBUTTONDOWN";
				activityManager::setActivity(new MenuActivity);
				exitActivity = 1;
				//*flag = 1;///��Ҫ©��*
				break;
			default:
				break;
			}
		}
	}
	return;
}

void MenuActivity::lifeCycle()
{
	//code for Menu
	cleardevice();
	IMAGE img2;
	loadimage(&img2, L"./Resource/�˵�����.jpg", 0, 0);
	putimage(0, 0, &img2);
	//�Ȼ�4����niu
	wchar_t arr1[] = L"��������";
	wchar_t arr2[] = L"�������";
	wchar_t arr3[] = L"��ʼ��Ϸ";
	wchar_t arr4[] = L"�˳���Ϸ";
	button(320, 100, 670, 170, arr1);
	button(320, 200, 670, 270, arr2);
	button(320, 300, 670, 370, arr3);
	button(320, 400, 670, 470, arr4);
	//����ÿ����ť��������ת��
	ExMessage msg;
	while (game::getRunningStatus() && !exitActivity)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 320 && msg.x <= 670 && msg.y >= 100 && msg.y <= 170)
				{
					activityManager::setActivity(new BackgroundIntroActivity);
					exitActivity = 1;
				}
				else if (msg.x >= 320 && msg.x <= 670 && msg.y >= 200 && msg.y <= 270)
				{

					activityManager::setActivity(new RuleIntroActivity);
					exitActivity = 1;
				}

				else if (msg.x >= 320 && msg.x <= 670 && msg.y >= 300 && msg.y <= 370)
				{
					activityManager::setActivity(new GamingActivity);
					exitActivity = 1;
				}
				else if (msg.x >= 320 && msg.x <= 670 && msg.y >= 400 && msg.y <= 470)
				{
					game::setRunningStatus(0);
					printf("�˳���Ϸ\n");
				}
				break;
			default:
				break;
			}
		}
	}
	return;
}

void PlayRuleIntroActivity::lifeCycle()
{
	//loop inside
	//code 
	cleardevice();
	IMAGE img3;
	loadimage(&img3, L"./Resource/�������.jpg", 0, 0);
	putimage(0, 0, &img3);
	wchar_t arr1[] = L"���˵�";
	wchar_t arr2[] = L"���ֽ���";

	button(914, 575, 110 + 914, 40 + 575, arr1);
	button(375, 317, 275 + 375, 120 + 317, arr2);

	ExMessage msg;
	while (game::getRunningStatus() && !exitActivity)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 914 && msg.x <= 110 + 914 && msg.y >= 575 && msg.y <= 40 + 575)
				{
					activityManager::setActivity(new MenuActivity);
					exitActivity = 1;
				}

				if (msg.x >= 375 && msg.x <= 275 + 375 && msg.y >= 317 && msg.y <= 120 + 317)
				{
					activityManager::setActivity(new TextRuleIntroActivity);
					exitActivity = 1;
				}
				break;
			default:
				break;
			}
		}
	}
	return;
}

void TextRuleIntroActivity::lifeCycle()
{
	//loop inside
	//code for 

	cleardevice();
	IMAGE img3;
	loadimage(&img3, L"./Resource/WordIntro.png", 0, 0);
	putimage(0, 0, &img3);
	wchar_t arr1[] = L"���˵�";

	button(914, 575, 110 + 914, 40 + 575, arr1);

	ExMessage msg;
	while (game::getRunningStatus() && !exitActivity)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 914 && msg.x <= 110 + 914 && msg.y >= 575 && msg.y <= 40 + 575)
				{
					activityManager::setActivity(new MenuActivity);
					exitActivity = 1;
				}
				break;
			default:
				break;
			}

		}
	}
	return;
}


void RuleIntroActivity::lifeCycle()
{
	//loop inside
	//code for RuleIntro
	cleardevice();
	IMAGE img3;
	loadimage(&img3, L"./Resource/����2.jpg", 0, 0);
	putimage(0, 0, &img3);
	wchar_t arr1[] = L"���˵�";
	wchar_t arr2[] = L"�������";
	wchar_t arr3[] = L"��������";
	button(457, 536, 110 + 457, 40 + 536, arr1);
	button(180, 192, 220 + 180, 162 + 192, arr2);
	button(620, 192, 220 + 620, 162 + 192, arr3);
	ExMessage msg;
	while (game::getRunningStatus() && !exitActivity)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 457 && msg.x <= 110 + 457 && msg.y >= 536 && msg.y <= 40 + 536)
				{
					activityManager::setActivity(new MenuActivity);
					exitActivity = 1;
				}

				if (msg.x >= 180 && msg.x <= 220 + 180 && msg.y >= 192 && msg.y <= 162 + 192)
				{
					activityManager::setActivity(new PlayRuleIntroActivity);
					exitActivity = 1;
				}
				if (msg.x >= 620 && msg.x <= 220 + 620 && msg.y >= 192 && msg.y <= 162 + 192)
				{
					activityManager::setActivity(new KeyBindingIntroActivity);
					exitActivity = 1;
				}
				break;
			default:
				break;
			}

		}

	}
	return;
}

void BackgroundIntroActivity::lifeCycle()
{
	//loop inside
	//code for 
	cleardevice();
	IMAGE img2;
	loadimage(&img2, L"./Resource/��������.jpg", 0, 0);
	putimage(0, 0, &img2);
	wchar_t arr1[] = L"���˵�";

	button(457, 536, 110 + 457, 40 + 536, arr1);

	ExMessage msg;
	while (game::getRunningStatus() && !exitActivity)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 457 && msg.x <= 110 + 457 && msg.y >= 536 && msg.y <= 40 + 536)
				{
					activityManager::setActivity(new MenuActivity);
					exitActivity = 1;
				}
				break;
			default:
				break;
			}

		}

	}
	return;
}

void KeyBindingIntroActivity::lifeCycle()
{
	//loop inside
	//code for 
	cleardevice();
	IMAGE img3;
	loadimage(&img3, L"./Resource/��������.jpg", 0, 0);
	putimage(0, 0, &img3);
	wchar_t arr1[] = L"���˵�";

	button(914, 575, 110 + 914, 40 + 575, arr1);

	ExMessage msg;
	while (game::getRunningStatus() && !exitActivity)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 914 && msg.x <= 110 + 914 && msg.y >= 575 && msg.y <= 40 + 575)
				{
					activityManager::setActivity(new MenuActivity);
					exitActivity = 1;
				}
				break;
			default:
				break;
			}
		}
	}
	return;
}
/*
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
}*/
