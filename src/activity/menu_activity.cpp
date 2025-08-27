
#include "menu_activity.h"
#include "background_intro_activity.hpp"
#include "game.h"
#include "gaming_activity.h"
#include "rule_intro_activity.hpp"
#include "utils.h"
#include <iostream>

void MenuActivity::lifeCycle() {
    // code for Menu
    cleardevice();
    IMAGE img2;
    loadimage(&img2, L"./resource/菜单界面.jpg", 0, 0);
    putimage(0, 0, &img2);
    // 先画4个按niu
    wchar_t arr1[] = L"背景故事";
    wchar_t arr2[] = L"规则介绍";
    wchar_t arr3[] = L"开始游戏";
    wchar_t arr4[] = L"退出游戏";
    button(320, 100, 670, 170, arr1);
    button(320, 200, 670, 270, arr2);
    button(320, 300, 670, 370, arr3);
    button(320, 400, 670, 470, arr4);
    // 设置每个按钮鼠标点击后的转跳
    ExMessage msg;
    while (game::getRunningStatus() && !exitActivity) {
        if (peekmessage(&msg, EX_MOUSE)) {
            switch (msg.message) {
            case WM_LBUTTONDOWN:
                if (msg.x >= 320 && msg.x <= 670 && msg.y >= 100 && msg.y <= 170) {
                    activityManager::setActivity(new BackgroundIntroActivity);
                    exitActivity = 1;
                } else if (msg.x >= 320 && msg.x <= 670 && msg.y >= 200 && msg.y <= 270) {

                    activityManager::setActivity(new RuleIntroActivity);
                    exitActivity = 1;
                }

                else if (msg.x >= 320 && msg.x <= 670 && msg.y >= 300 && msg.y <= 370) {
                    activityManager::setActivity(new GamingActivity);
                    exitActivity = 1;
                } else if (msg.x >= 320 && msg.x <= 670 && msg.y >= 400 && msg.y <= 470) {
                    game::setRunningStatus(0);
                    std::cout << "退出游戏\n";
                }
                break;
            default:
                break;
            }
        }
    }
}
