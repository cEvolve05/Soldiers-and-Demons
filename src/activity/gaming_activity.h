#pragma once
#include "activity.h"
#include "board.h"
#include <queue>

class GamingActivity final : public activity {
  public:
    void lifeCycle() override;

  private:
    ExMessage m;
    std::queue<int> input;

    board *L, *R;

    wordProcess* wordProc;

    void init();
    void end();

    void inputFilter();
    void process();
    void render();
};