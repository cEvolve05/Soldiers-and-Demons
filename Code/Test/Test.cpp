#include <graphics.h>
#include <iostream>
#include "resource.h"

using namespace std;

int main()
{
	const int windowX = 500;
	const int windowY = 500;
	const POINT windowPoint[] = { {0,0},{0,windowY},{windowX,windowY},{windowX,0} };
	//const wchar_t playerImagePath[] = L"player.png";
	ExMessage m;
	IMAGE player;
	POINT playerLocation = { windowX / 2, windowY / 2 };

	initgraph(windowX, windowY);


	loadimage(&player, L"PNG", MAKEINTRESOURCE(RESplayer));

	//IMPORTANT: must flush draw after every draw
	BeginBatchDraw();

	//player need to be encapsulated

	putimage(playerLocation.x, playerLocation.y, &player);

	FlushBatchDraw();

	while (true)
	{
		Sleep(17);
		flushmessage(EX_MOUSE | EX_CHAR);
		peekmessage(&m, EX_MOUSE | EX_KEY);

		switch (m.message)
		{
		case WM_MOUSEMOVE:
			putpixel(m.x, m.y, RED);
			break;

		case WM_KEYDOWN:
			switch (m.vkcode)
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

			case VK_ESCAPE:
				closegraph();
				return 0;

			default:
				break;
			}



		default:
			break;
		}


		cout << playerLocation.x << " & " << playerLocation.y << endl;

		clearpolygon(windowPoint, 4);
		putimage(playerLocation.x, playerLocation.y, &player);
		FlushBatchDraw();
	}

	return 0;
}