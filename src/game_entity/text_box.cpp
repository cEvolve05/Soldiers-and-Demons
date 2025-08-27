#include "text_box.h"
#include "utils.h"

textBox::textBox() {
    // constructor
    this->from = {0, 0};
    this->to = {0, 0};
    // addWord(new word{ L"我",1,0 });
}

textBox::~textBox() {
    // destructor
    words.clear();
    for (auto iter = words.begin(); iter != words.end(); iter++) {
        delete (*iter);
    }
}

void textBox::addWord(word* INword) {
    // add word to the word list
    this->words.push_back(INword);
    return;
}

void textBox::empty() {
    // empty the word list
    for (int i = 0; i < words.size(); i++) {
        delete words[i];
    }
    this->words.clear();
    return;
}

void textBox::setLocation(POINT from, POINT to) {
    // set the size of the text box
    this->from = from;
    this->to = to;
    return;
}

void textBox::render() {
    // clearrectangle(from.x, from.y, to.x, to.y);
    fillrectangle(from.x, from.y, to.x, to.y);
    setcliprgn(CreateRectRgn(from.x, from.y, to.x, to.y));

    int y1 = from.y + 2, y2 = to.y - 2, x1 = from.x + 2;
    settextstyle(y2 - y1 - 4, 0, L"黑体");
    for (auto iter = words.begin(); iter != words.end(); iter++) {
        fillrectangle(x1, y1, x1 + textwidth((*iter)->text.c_str()) + 2, y2);
        outtextxy(x1 + 2, y1 + 2, (LPCTSTR)(*iter)->text.c_str());
        x1 = x1 + textwidth((*iter)->text.c_str()) + 2 + 2;
    }

    setcliprgn(NULL);
    return;
}
