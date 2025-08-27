#include "game.h"
#include "activity_manager.h"
#include "start_activity.hpp"
#include "utils.h"

game::game() {
    this->running = 1;
    // std::cout << typeid(this).name() << std::endl;
}

bool game::getRunningStatus() { return running; }

void game::setRunningStatus(bool status) { running = status; }

void game::entry() {
    init();
    activityManager::showActivity();
    end();
}

void game::init() {
    initgraph(windowSize::X, windowSize::Y, EX_SHOWCONSOLE | EW_NOCLOSE);
    activityManager::setActivity(new StartActivity);
}

void game::end() { closegraph(); }
