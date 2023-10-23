#include <graphics.h>
#include <iostream>
#include <winuser.h>

#include <wchar.h>//Debug

#include "resource.h"

#define DEBUG

using namespace std;
/*
int main()
{
	const int windowX = 500;
	const int windowY = 500;
	const POINT windowPoint[] = { {0,0},{0,windowY},{windowX,windowY},{windowX,0} };
	//const wchar_t playerImagePath[] = L"player.png";
	ExMessage m;
	IMAGE player;
	POINT playerLocation = { windowX / 2, windowY / 2 };
	char userLastInput=0;

	initgraph(windowX, windowY, EX_SHOWCONSOLE);


	loadimage(&player, L"PNG", MAKEINTRESOURCE(RESplayer));

	//IMPORTANT: must flush draw after every draw
	BeginBatchDraw();

	//player need to be encapsulated

	putimage(playerLocation.x, playerLocation.y, &player);

	FlushBatchDraw();

	while (true)
	{
		//flushmessage(EX_MOUSE | EX_CHAR);
		//Input Process
		while(peekmessage(&m, EX_MOUSE | EX_KEY))
		{
			switch (m.message)
			{
			case WM_MOUSEMOVE:
				putpixel(m.x, m.y, RED);
				break;

			case WM_KEYDOWN:

#ifdef DEBUG
				cout << "KEY_DOWN" << m.vkcode << "   " << GetKeyState(userLastInput);
#endif // DEBUG

				//switch (m.vkcode)
				//{
				//case 'W':
				//	userLastInput = 'W';
				//	break;

				//case 'S':
				//	userLastInput = 'S';
				//	break;

				//case 'A':
				//	userLastInput = 'A';
				//	break;

				//case 'D':
				//	userLastInput = 'D';
				//	break;

				//case VK_ESCAPE:
				//	closegraph();
				//	return 0;

				//default:
				//	break;
				//}

				if (m.vkcode == VK_ESCAPE)
				{
					closegraph();
					return 0;
				}
				if (m.vkcode == 'W' || m.vkcode == 'S' || m.vkcode == 'A' || m.vkcode == 'D')
					userLastInput = m.vkcode;

			case WM_KEYUP:

#ifdef DEBUG
				cout << "KEY_UP" << m.vkcode << "   "<< GetKeyState(userLastInput);
#endif // DEBUG

				if (m.vkcode == userLastInput && ~(GetKeyState(userLastInput) >> 7 ))
					userLastInput = 0;
				break;

			default:
				break;
			}
#ifdef DEBUG
			cout <<"               " << m.vkcode << " & " << userLastInput << endl;//Debug
#endif // DEBUG
		}

		//Object Update
		switch (userLastInput)
		{
		case 'W':
			playerLocation.y -= 5;
			break;

		case 'S':
			playerLocation.y += 5;
			break;

		case 'A':
			playerLocation.x -= 5;
			break;

		case 'D':
			playerLocation.x += 5;
			break;

		default:
			break;
		}

#ifdef DEBUG
		cout << "                              " << playerLocation.x << " & " << playerLocation.y << endl;//Debug
#endif // DEBUG

		//Render
		clearpolygon(windowPoint, 4);
		putimage(playerLocation.x, playerLocation.y, &player);
		FlushBatchDraw();
		Sleep(17);
	}

	return 0;
}*/

#include "board.h"
int main()
{
	initgraph(500, 500);
	board testBoard;
	testBoard.setBoardLocation({ 0,0 });
	testBoard.setBoardSize({ 5,5 });
	testBoard.setGridSize({ 90,90 });
	testBoard.render();

	
	getchar();
	return 0;
}