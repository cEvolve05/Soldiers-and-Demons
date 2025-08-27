#pragma once
#include "activity.h"
#include "activity_manager.h"
#include "game.h"
#include "menu_activity.h"

class BackgroundIntroActivity final : public activity {
  public:
    void lifeCycle() {
        // loop inside
        // code for
        cleardevice();
        IMAGE img2;
        loadimage(&img2, L"./resource/背景故事.jpg", 0, 0);
        putimage(0, 0, &img2);
        wchar_t arr1[] = L"主菜单";

        button(457, 536, 110 + 457, 40 + 536, arr1);

        ExMessage msg;
        while (game::getRunningStatus() && !exitActivity) {
            if (peekmessage(&msg, EX_MOUSE)) {
                switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if (msg.x >= 457 && msg.x <= 110 + 457 && msg.y >= 536 && msg.y <= 40 + 536) {
                        activityManager::setActivity(new MenuActivity);
                        exitActivity = 1;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
};