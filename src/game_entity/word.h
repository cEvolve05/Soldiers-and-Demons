#pragma once
#include "utils.h"
#include <string>

class word {
  public:
    enum wordType {
        Subject,
        Verb,
        Item,
        Action,
        Special,
        COUNT // Last one
    };

    word(std::wstring text, int length = 0, wordType type = COUNT);
    void render(POINT from, POINT to) const;

    std::wstring text;
    int length;
    wordType type;
};

// class verbBlock : public word
// TODO

// class nounBlock : public word
// TODO