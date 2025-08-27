#include "word.h"
#include "utils.h"

word::word(std::wstring text, int length, wordType type) {
    this->text = text;
    if (length == 0) {
        this->length = text.size();
    } else {
        this->length = length;
    }
    this->type = type;
}

void word::render(POINT from, POINT to) const {
    fillrectangle(from.x, from.y, to.x, to.y);
    settextstyle(to.y - from.y - 4, 0, L"黑体");
    // if (textwidth((LPCTSTR)text.c_str()) > length)
    //{
    //	std::cout << "text too long" << std::endl;
    // }
    outtextxy((to.x - from.x - textwidth(this->text.c_str())) / 2 + from.x,
              (to.y - from.y - textheight(this->text.c_str())) / 2 + from.y, (LPCTSTR)text.c_str());
}