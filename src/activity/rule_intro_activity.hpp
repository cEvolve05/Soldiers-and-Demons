#pragma once
#include "activity.h"
#include "activity_manager.h"
#include "game.h"
#include "keybinding_intro_activity.hpp"
#include "menu_activity.h"
#include "play_rule_intro_activity.hpp"

class RuleIntroActivity final : public activity {
  public:
    void lifeCycle() {
        // loop inside
        // code for RuleIntro
        cleardevice();
        IMAGE img3;
        loadimage(&img3, L"./resource/纹理2.jpg", 0, 0);
        putimage(0, 0, &img3);
        wchar_t arr1[] = L"主菜单";
        wchar_t arr2[] = L"规则介绍";
        wchar_t arr3[] = L"按键介绍";
        button(457, 536, 110 + 457, 40 + 536, arr1);
        button(180, 192, 220 + 180, 162 + 192, arr2);
        button(620, 192, 220 + 620, 162 + 192, arr3);
        ExMessage msg;
        while (game::getRunningStatus() && !exitActivity) {
            if (peekmessage(&msg, EX_MOUSE)) {
                switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if (msg.x >= 457 && msg.x <= 110 + 457 && msg.y >= 536 && msg.y <= 40 + 536) {
                        activityManager::setActivity(new MenuActivity);
                        exitActivity = 1;
                    }

                    if (msg.x >= 180 && msg.x <= 220 + 180 && msg.y >= 192 && msg.y <= 162 + 192) {
                        activityManager::setActivity(new PlayRuleIntroActivity);
                        exitActivity = 1;
                    }
                    if (msg.x >= 620 && msg.x <= 220 + 620 && msg.y >= 192 && msg.y <= 162 + 192) {
                        activityManager::setActivity(new KeyBindingIntroActivity);
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