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
	initgraph(640, 480);

	settextstyle(20, 0, L"黑体");
	outtextxy(100, 100, L"Hello World!中文");

	_getch();
	
	return 0;
}