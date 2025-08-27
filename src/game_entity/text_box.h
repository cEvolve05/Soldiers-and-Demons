#pragma once
#include "utils.h"
#include "word.h"
#include <vector>

class textBox {
    friend class wordProcess;

  public:
    textBox();
    ~textBox();

    void addWord(word* INword);
    void empty();

    void setLocation(POINT from, POINT to);

    void render();

  private:
    std::vector<word*> words;
    POINT from, to;
};
