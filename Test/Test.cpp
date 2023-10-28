#include <graphics.h>
#include <iostream>
#include <winuser.h>
#include <winnt.h>
#include <conio.h>

#include <wchar.h>//Debug

#include "resource.h"

#define DEBUG

using namespace std;

int main()
{
	initgraph(1024, 615);
	IMAGE background;
	loadimage(&background, L"./Resource/开始界面.png", 0, 0);
	putimage(0, 0, &background);

	_getch();
	
	return 0;
}