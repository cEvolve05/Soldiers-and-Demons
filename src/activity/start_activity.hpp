#pragma once
#include "activity.h"
#include "menu_activity.h"

class StartActivity final : public activity {
  public:
    void lifeCycle() override {
        // code for Start
        // initgraph(1024, 615, EX_SHOWCONSOLE);
        IMAGE background;
        loadimage(&background, L"./resource/开始界面.png", 0, 0);
        putimage(0, 0, &background);
        ExMessage msg;
        while (game::getRunningStatus() && !exitActivity) {
            // std::cout << peekmessage(&msg, EX_MOUSE, false);
            if (peekmessage(&msg, EX_MOUSE)) // 有鼠标消息就返回真，没有返回假
            {
                switch (msg.message) {
                case WM_LBUTTONDOWN: // 区分左右键,单击鼠标左键
                    // std::cout << "WM_LBUTTONDOWN";
                    activityManager::setActivity(new MenuActivity);
                    exitActivity = 1;
                    //*flag = 1;///不要漏掉*
                    break;
                default:
                    break;
                }
            }
        }
    }
};
