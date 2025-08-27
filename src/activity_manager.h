#pragma once
#include "activity.h"

class activityManager {
  public:
    inline static bool exitActivity = false;

    static void setActivity(activity* a);
    static void showActivity();

  private:
    activityManager();
    ~activityManager();
    inline static activity* currentActivity = nullptr;
};