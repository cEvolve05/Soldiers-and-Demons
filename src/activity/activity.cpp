#include "activity.h"
#include "utils.h"
#include <graphics.h>
#include <iostream>

activity::activity() : exitActivity(0) { std::cout << typeid(this).name() << std::endl; }

activity::~activity() {}

void activity::button(int x1, int y1, int x2, int y2, wchar_t arr[]) {
    setfillcolor(RGB(240, 155, 89));
    fillrectangle(x1, y1, x2, y2);
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(40, 0, L"楷体");
    int w = (x2 - x1 - textwidth(arr)) / 2;
    int h = (y2 - y1 - textheight(arr)) / 2;
    outtextxy(x1 + w, y1 + h, arr);
    setfillcolor(WHITE);
}