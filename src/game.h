#pragma once

class game {
  public:
    game();
    void entry();

    static bool getRunningStatus();
    static void setRunningStatus(bool status);

  private:
    inline static bool running = false;

    void init();
    void end();
};