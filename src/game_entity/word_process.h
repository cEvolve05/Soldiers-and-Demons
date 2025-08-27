#pragma once

#include "board.h"
#include "word.h"

class wordProcess {
  public:
    wordProcess();
    ~wordProcess();

    struct possibilityBlock {
        word word;
        unsigned short int possibility;
    };

    void generateWord(board* targetBoard);
    bool applySentence(board* from, board* to);

    void DEBUGremoveBlock(board* target);

  private:

    void useItem(word* item, board* from, board* to);
    void makeAction(word* item, board* from, board* to);

    void removeBlock(board* target);
    void blockBoard(board* target);

    std::vector<std::vector<possibilityBlock>> data;
    std::vector<int> size; // auto generate

    std::vector<double> typePossibility;
    std::vector<std::vector<double>> wordPossibility; // auto
};
