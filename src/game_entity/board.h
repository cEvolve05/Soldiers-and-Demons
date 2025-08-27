#pragma once
#include "role.h"
#include "text_box.h"
#include "utils.h"
#include <chrono>

class board {
    friend class wordProcess;
    friend class GamingActivity;

  public:
    board();
    ~board();

    role* player;
    POINT playerLocation; // grid location

    textBox* sentence;

    // render from from to to
    void setBoardLocation(POINT from, POINT to);
    // size{4,5} meaning 4*5 board
    void setGrid(POINT grid);
    void init();

    void setPlayerLocation(POINT location);
    void getGridLocation(POINT& from, POINT& to, POINT gridLocationFrom, POINT gridLocationTo = {-1, -1}) const;
    POINT getGridLocation(POINT location);
    bool addWord(word* word, POINT wordHeadLocation);
    word* getWord(POINT location);
    void delWord(POINT location);

    void removeBlock();

    void render() const;

  private:
    IMAGE HP;
    struct wordBlock {
        word* word;
        POINT headLocation;
    };
    POINT from, to;                    // for location
    POINT grid;                        // for board grid
    std::vector<wordBlock*> wordVault; // 存放所有的wordVault的指针的向量
    wordBlock*** WordInBoard;          // 一个存放各个格子的（指向这个格子对应的wordVault的指针）的二维数组
    int** BlockedGrid;
    std::chrono::steady_clock::time_point removeBlockTimer;
    bool blocked = 0;

    // Auto generate:
    DWORD lineWidth;
    POINT gridBlankSize;
};