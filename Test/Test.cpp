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


	ExMessage m;
	initgraph(100, 100);
	int p = 0;
	while (true)
	{

		while (peekmessage(&m, EX_MOUSE | EX_KEY))
		{
			cout << "       " << m.vkcode << "     " << m.prevdown << endl;

			if ((m.vkcode == 'W' || m.vkcode == 'S' || m.vkcode == 'A' || m.vkcode == 'D') && m.prevdown == 0)
			{
				p = 0;
			}
			if (p == 0)
			{
				cout << m.vkcode<<endl;
				p = 1;
			}

		}
			cout << "---------------"<<endl;
			Sleep(17);
	}

	
	
	return 0;
}