#pragma once
#include "activity.h"
#include "activity_manager.h"
#include "game.h"
#include "menu_activity.h"

class KeyBindingIntroActivity final : public activity {
  public:
    void lifeCycle() override {
        // loop inside
        // code for
        cleardevice();
        IMAGE img3;
        loadimage(&img3, L"./resource/按键介绍.jpg", 0, 0);
        putimage(0, 0, &img3);
        wchar_t arr1[] = L"主菜单";

        button(914, 575, 110 + 914, 40 + 575, arr1);

        ExMessage msg;
        while (game::getRunningStatus() && !exitActivity) {
            if (peekmessage(&msg, EX_MOUSE)) {
                switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if (msg.x >= 914 && msg.x <= 110 + 914 && msg.y >= 575 && msg.y <= 40 + 575) {
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