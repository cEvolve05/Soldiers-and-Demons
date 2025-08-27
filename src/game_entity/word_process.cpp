#include "word_process.h"
#include <iostream>

wordProcess::wordProcess() {
    // constructor

    // data
    {
        // Subject
        this->data.push_back({
            {{L"勇者", 2, word::Subject}, 1},
            {{L"魔王", 2, word::Subject}, 1},
        });

        // Verb
        this->data.push_back({
            {{L"使用", 2, word::Verb}, 1},
            //{{L"进行",0,word::Verb},1},
            //{{L"释放",0,word::Verb},1},
            {{L"使出", 2, word::Verb}, 2},
        });

        // Object
        this->data.push_back({
            {{L"食物", 2, word::Item}, 5},
            {{L"药剂", 2, word::Item}, 3},
        });

        // Action
        this->data.push_back({
            {{L"攻击", 2, word::Action}, 3}, {{L"强力攻击", 4, word::Action}, 2},
            //{{L"防御",2,word::Action},1},
        });

        // Special
        this->data.push_back({
            {{L"清空文本框", 5, word::Special}, 2},
            {{L"移除词块", 4, word::Special}, 1},
            {{L"生成词块", 4, word::Special}, 1},
            {{L"禁用棋盘", 4, word::Special}, 2},
        });
    }

    // data size
    {
        this->size.reserve(word::wordType::COUNT);
        for (int i = 0; i < word::wordType::COUNT; i++) {
            this->size.push_back(data[i].size());
        }
    }

    // type possibility
    {
        int typePossibilityRatio[word::wordType::COUNT]{2, 2, 2, 2, 3};
        this->typePossibility.reserve(word::wordType::COUNT);
        int typePossibilitySum = 0;
        for (int i = 0; i < word::wordType::COUNT; i++) {
            typePossibilitySum += typePossibilityRatio[i];
        }
        for (int i = 0; i < word::wordType::COUNT; i++) {
            this->typePossibility.push_back(double(typePossibilityRatio[i]) / double(typePossibilitySum));
        }
    }

    // word possibility
    {
        // allocate
        this->wordPossibility.reserve(word::wordType::COUNT);
        for (int i = 0; i < word::wordType::COUNT; i++) {
            wordPossibility.push_back(std::vector<double>(size[i]));
        }

        int wordPossibilitySum[word::wordType::COUNT] = {0};
        for (int i = 0; i < word::wordType::COUNT; i++) {
            for (int j = 0; j < size[i]; j++) {
                wordPossibilitySum[i] += data[i][j].possibility;
            }
            std::cout << std::endl;
        }
        for (int i = 0; i < word::wordType::COUNT; i++) {
            for (int j = 0; j < size[i]; j++) {
                wordPossibility[i][j] = double(data[i][j].possibility) / double(wordPossibilitySum[i]);
            }
        }
    }

    // for (int i = 0; i < 5; i++)
    //{
    //	this->size[i] = sizeof(data[i]) / sizeof(word);
    // }
}

wordProcess::~wordProcess() {
    // destructor
}

int logcat[10][10] = {};

void wordProcess::generateWord(board* targetBoard) {
    double random;

    // word type
    int targetType = rand() % 5;
    random = double(rand()) / double(RAND_MAX);
    for (int i = 0; i < word::wordType::COUNT; i++) {
        random -= typePossibility[i];
        if (random < 0.0) {
            targetType = i;
            break;
        }
    }

    // word detail
    int wordIndex = rand() % size[targetType];
    random = double(rand()) / double(RAND_MAX);
    for (int i = 0; i < size[targetType]; i++) {
        random -= wordPossibility[targetType][i];
        if (random < 0.0) {
            wordIndex = i;
            break;
        }
    }

    board::wordBlock*** boardStatue = targetBoard->WordInBoard;

    // word location
    int wordSize = data[targetType][wordIndex].word.length;
    int count = 0;
    POINT headLocation;
    for (int i = 0; i < 5; i++) {
        headLocation = {rand() % (targetBoard->grid.x - (wordSize - 1)), rand() % targetBoard->grid.y};
        for (int i = 0; i < wordSize; i++) {
            count += bool(boardStatue[headLocation.x + i][headLocation.y]);
        }
        if (count == 0) {
            logcat[targetType][wordIndex] += 1;
            if (targetType == word::Subject) {
                word* tmp = new word{data[targetType][wordIndex].word};
                tmp->text = targetBoard->player->label;
                targetBoard->addWord(tmp, headLocation);
                break;
            }
            targetBoard->addWord(new word{data[targetType][wordIndex].word}, headLocation);
            break;
        }
    }
}

bool wordProcess::applySentence(board* from, board* to) {
    std::vector<word*>& sentence = from->sentence->words;

    if (sentence.size() != 3) {
        from->sentence->empty();
        return false;
    }

    if (sentence[0]->text != from->player->label || sentence[1]->type != word::Verb) {
        from->sentence->empty();
        return false;
    }

    if ((sentence[1]->text == L"使用" && sentence[2]->type != word::Item) ||
        (sentence[1]->text == L"使出" && sentence[2]->type == word::Item)) {
        from->sentence->empty();
        return false;
    }

    if (sentence[1]->text == L"使用") {
        useItem(sentence[2], from, to);
    } else if (sentence[1]->text == L"使出") {
        makeAction(sentence[2], from, to);
    }
    from->sentence->empty();
    return true;
}

void wordProcess::useItem(word* item, board* from, board* to) {
    if (item->text == L"食物") {
        from->player->shiftProerty(role::HealthPoint, +1);
    } else if (item->text == L"药剂") {
        from->player->shiftProerty(role::HealthPoint, +2);
    }
}

void wordProcess::makeAction(word* item, board* from, board* to) {
    // Action
    if (item->text == L"攻击") {
        to->player->shiftProerty(role::HealthPoint, -1);
    } else if (item->text == L"强力攻击") {
        to->player->shiftProerty(role::HealthPoint, -2);
    } else if (item->text == L"防御") {
        from->player->shiftProerty(role::Defence, -1);
    }
    // Special
    else if (item->text == L"清空文本框") {
        to->sentence->empty();
    } else if (item->text == L"移除词块") {
        removeBlock(to);
    } else if (item->text == L"生成词块") {
        for (int i = 0; i < 5; i++) {
            generateWord(from);
        }
    } else if (item->text == L"禁用棋盘") {
        blockBoard(to);
    }
}

void wordProcess::removeBlock(board* target) {
    int cycleTime = target->wordVault.size() * 0.5; // decide % to remove
    for (int i = 0; i < cycleTime; i++) {
        target->delWord(target->wordVault[rand() % target->wordVault.size()]->headLocation);
    }
}

void wordProcess::DEBUGremoveBlock(board* target) {
    for (int i = 0; i < target->wordVault.size(); i++) {
        target->delWord(target->wordVault[0]->headLocation);
    }
}

void wordProcess::blockBoard(board* target) {
    int cycleTime = target->grid.x * target->grid.y * 0.3; // decide % to block
    for (int i = 0; i < cycleTime; i++) {
        POINT location = {rand() % target->grid.x, rand() % target->grid.y};
        if (target->BlockedGrid[location.x][location.y] == 0) {
            target->BlockedGrid[location.x][location.y] = 1;
        } else {
            i--;
        }
    }

    target->removeBlockTimer = std::chrono::steady_clock::now();
    target->blocked = 1;
}