#include "gaming_activity.h"
#include "activity_manager.h"
#include "game.h"
#include "menu_activity.h"
#include "utils.h"
#include "word_process.h"
#include <graphics.h>
#include <iostream>

void GamingActivity::init() {
    BeginBatchDraw();
    this->m = {0};

    L = new board;
    L->setBoardLocation({40, 40}, {40 + 411, 40 + 411});
    L->setGrid({10, 10});
    L->init();
    L->player->label = L"勇者";
    L->player->setImg(L"./resource/Soldier.png", L->gridBlankSize);
    L->sentence->setLocation({40, windowSize::Y - 40 - 45}, {40 + 411, windowSize::Y - 40});

    R = new board;
    R->setBoardLocation({windowSize::X - 40 - 411, 40}, {windowSize::X - 40, 40 + 411});
    R->setGrid({10, 10});
    R->init();
    R->player->label = L"魔王";
    R->player->setImg(L"./resource/Demon.png", R->gridBlankSize);
    R->sentence->setLocation({windowSize::X - 40 - 411, windowSize::Y - 40 - 45},
                             {windowSize::X - 40, windowSize::Y - 40});

    wordProc = new wordProcess;

    setfillcolor(WHITE);
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 1);
}

void GamingActivity::end() {
    delete L, R;
    EndBatchDraw();
}

void GamingActivity::lifeCycle() {
    // loop inside
    // code for Gaming
    cleardevice();
    button(457, 536, 457 + 110, 536 + 40, (wchar_t*)L"主菜单");
    init();
    // L->addWord(new word{ L"魔王",2 ,word::Subject }, { 0,0 });
    for (int i = 0; i < 5; i++) {
        wordProc->generateWord(L);
        wordProc->generateWord(R);
    }

    while (game::getRunningStatus() && !exitActivity) {
        // std::cout << "cycle start" << std::endl;
        inputFilter();
        process();
        render();
        Sleep(8);
    }
    end();
}

void GamingActivity::inputFilter() {
    // std::cout << "inputFilter" << std::endl;
    // flushmessage(EX_MOUSE | EX_CHAR);
    // Input Process
    while (peekmessage(&m, EX_MOUSE | EX_KEY | EX_WINDOW)) {
        switch (m.message) {
        case WM_LBUTTONDOWN:
            if (m.x >= 457 && m.x <= 457 + 110 && m.y >= 536 && m.y <= 536 + 40) {
                activityManager::setActivity(new MenuActivity);
                exitActivity = 1;
                return;
            }
            break;
        case WM_MOUSEMOVE:
            // putpixel(m.x, m.y, RED);
            break;

        case WM_KEYDOWN:
            if (m.vkcode == VK_ESCAPE) {
                game::setRunningStatus(0);
                return;
            }
            if (m.prevdown == 0) {
                input.push(m.vkcode);
            }
            break;

        case WM_QUIT:
            game::setRunningStatus(0);
            return;
            break;
        default:
            break;
        }
    }
}

void GamingActivity::process() {
    // input process
    while (input.empty() == 0) {
        switch (input.front()) {

        case 'W':
            // Left Role Move Up
            this->L->setPlayerLocation({this->L->playerLocation.x, this->L->playerLocation.y - 1});
            break;
        case 'A':
            // Left Role Move Left
            this->L->setPlayerLocation({this->L->playerLocation.x - 1, this->L->playerLocation.y});
            break;
        case 'S':
            // Left Role Move Down
            this->L->setPlayerLocation({this->L->playerLocation.x, this->L->playerLocation.y + 1});
            break;
        case 'D':
            // Left Role Move Right
            this->L->setPlayerLocation({this->L->playerLocation.x + 1, this->L->playerLocation.y});
            break;
        case 'F':
            // Left Role get word
            if (bool(L->getWord(L->playerLocation))) {
                L->sentence->addWord(L->getWord(L->playerLocation));
                L->delWord(L->playerLocation);
            }
            break;
        case 'E':
            // erase textBox
            L->sentence->empty();
            break;
        case 'R':
            // apply sentence
            wordProc->applySentence(L, R);
            break;

        case 'U':
            // Right Role Move Up
            this->R->setPlayerLocation({this->R->playerLocation.x, this->R->playerLocation.y - 1});
            break;
        case 'H':
            // Right Role Move Left
            this->R->setPlayerLocation({this->R->playerLocation.x - 1, this->R->playerLocation.y});
            break;
        case 'J':
            // Right Role Move Down
            this->R->setPlayerLocation({this->R->playerLocation.x, this->R->playerLocation.y + 1});
            break;
        case 'K':
            // Right Role Move Right
            this->R->setPlayerLocation({this->R->playerLocation.x + 1, this->R->playerLocation.y});
            break;
        case 'L':
            // Right Role get word
            if (bool(R->getWord(R->playerLocation))) {
                R->sentence->addWord(R->getWord(R->playerLocation));
                R->delWord(R->playerLocation);
            }
            break;
        case 'I':
            // erase textBox
            R->sentence->empty();
            break;
        case 'O':
            // apply sentence
            wordProc->applySentence(R, L);
            break;

        case 'C':
            wordProc->DEBUGremoveBlock(L);
            break;
        case 'V':
            wordProc->DEBUGremoveBlock(R);
            break;
        case VK_ESCAPE:
            // Exit Game
            activityManager::setActivity(new MenuActivity);
            exitActivity = 1;
            EndBatchDraw();
            return;
            break;
        }
        input.pop();
    }

    using namespace std::chrono;

    // generate word
    static auto generateTimer = steady_clock::now();
    if (duration_cast<milliseconds>(steady_clock::now() - generateTimer).count() > 200) {
        generateTimer = steady_clock::now();
        wordProc->generateWord(L);
        wordProc->generateWord(R);
    }

    if (L->blocked == 1 && duration_cast<seconds>(steady_clock::now() - L->removeBlockTimer).count() > 5) {
        L->removeBlock();
    }
    if (R->blocked == 1 && duration_cast<seconds>(steady_clock::now() - R->removeBlockTimer).count() > 5) {
        R->removeBlock();
    }
    // L->player->property[role::HealthPoint] -= 1;
}

void GamingActivity::render() {
    // std::cout << "render" << std::endl;

    if (L->player->property[role::HealthPoint] < 1 || R->player->property[role::HealthPoint] < 1) {
        std::cout << "勇者血量：" << L->player->property[role::HealthPoint] << std::endl;
        std::cout << "魔王血量：" << R->player->property[role::HealthPoint] << std::endl;

        POINT from{windowSize::X / 2 * 0.382, windowSize::Y / 2 * 0.382},
            to{windowSize::X / 2 * 1.618, windowSize::Y / 2 * 1.618};

        IMAGE img;
        loadimage(&img, L"./resource/Background.jpg", 0, 0);
        putimage(0, 0, &img);
        fillrectangle(from.x, from.y, to.x, to.y);

        std::wstring text = std::format(
            L"{}胜利",
            L->player->property[role::HealthPoint] > R->player->property[role::HealthPoint] ? L"勇者" : L"魔王");
        std::wstring text2 = std::format(L"勇者血量：{}    魔王血量：{}", L->player->property[role::HealthPoint],
                                         R->player->property[role::HealthPoint]);

        outtextxy((to.x - from.x - textwidth(text.c_str())) / 2 + from.x,
                  (to.y - from.y - textheight(text.c_str())) / 2 + from.y - textheight(text2.c_str()),
                  (LPCTSTR)text.c_str());
        outtextxy((to.x - from.x - textwidth(text2.c_str())) / 2 + from.x,
                  (to.y - from.y - textheight(text2.c_str())) / 2 + from.y, (LPCTSTR)text2.c_str());

        button(457, 536, 457 + 110, 536 + 40, (wchar_t*)L"主菜单");
        FlushBatchDraw();
        while (true) {
            getmessage(&m, EX_MOUSE);
            if (m.message == WM_LBUTTONDOWN && m.x >= 457 && m.x <= 457 + 110 && m.y >= 536 && m.y <= 536 + 40) {
                activityManager::setActivity(new MenuActivity);
                exitActivity = 1;
                return;
            }
        }
        return;
    }

    IMAGE img;
    loadimage(&img, L"./resource/Background.jpg", 0, 0);
    putimage(0, 0, &img);
    L->render();
    L->sentence->render();
    R->render();
    R->sentence->render();
    button(457, 536, 457 + 110, 536 + 40, (wchar_t*)L"主菜单");
    FlushBatchDraw();
}