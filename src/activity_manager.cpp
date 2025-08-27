#include "activity_manager.h"
#include "game.h"

activityManager::activityManager() {
    // std::cout << typeid(this).name() << std::endl;
}

activityManager::~activityManager() {}

void activityManager::showActivity() {
    while (game::getRunningStatus()) {
        currentActivity->lifeCycle();
    }
}

void activityManager::setActivity(activity* a) { currentActivity = a; }
