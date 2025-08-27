#include "board.h"
#include "activity.h"
#include "utils.h"

board::board() {
    this->grid = {0};
    this->from = {0};
    this->to = {0};
    this->WordInBoard = NULL;
    this->lineWidth = {0};
    this->gridBlankSize = {0};
    this->player = new role;
    this->playerLocation = {0};
    this->sentence = new textBox;
    this->BlockedGrid = {0};
    loadimage(&this->HP, L"./resource/HP.png");
}

board::~board() {
    // destructor
    for (auto iter = this->wordVault.begin(); iter != this->wordVault.end(); iter++) {
        delete (*iter);
    }

    for (int i = 0; i < this->grid.x; i++) {
        delete this->WordInBoard[i];
    }
    delete this->WordInBoard;

    wordVault.clear();

    delete player;
    delete sentence;
}

void board::setBoardLocation(POINT from, POINT to) {
    this->from = from;
    this->to = to;
    return;
}

void board::setGrid(POINT grid) {
    this->grid = grid;
    return;
}

void board::init() {
    LINESTYLE pstyle;
    getlinestyle(&pstyle);
    this->lineWidth = pstyle.thickness;

    POINT gridBlankSize = {(this->to.x - this->from.x + 1 - lineWidth * (grid.x + 1)) / grid.x,
                           (this->to.y - this->from.y + 1 - lineWidth * (grid.y + 1)) / grid.y};
    this->gridBlankSize = gridBlankSize;

    // init WordInBoard
    this->WordInBoard = new wordBlock**[grid.x];
    for (int i = 0; i < grid.x; i++) {
        WordInBoard[i] = (new wordBlock* [grid.y] { NULL });
    }

    this->BlockedGrid = new int*[grid.x];
    for (int i = 0; i < grid.x; i++) {
        BlockedGrid[i] = (new int[grid.y]{0});
    }

    // init role
    this->setPlayerLocation({0, 0});

    return;
}

void board::setPlayerLocation(POINT location) {
    if (location.x < 0 || location.y < 0 || location.x > this->grid.x - 1 || location.y > this->grid.y - 1 ||
        BlockedGrid[location.x][location.y] == 1) {
        return;
    }
    this->playerLocation = location;
    POINT tmp = getGridLocation(location);
    this->player->setLocation({tmp.x + 1, tmp.y + 1});
    return;
}

void board::getGridLocation(POINT& from, POINT& to, POINT gridLocationFrom, POINT gridLocationTo) const {
    if (gridLocationTo.x == -1 && gridLocationTo.y == -1) {
        gridLocationTo = gridLocationFrom;
    }

    POINT OUTfrom = {this->from.x + lineWidth + gridLocationFrom.x * (lineWidth + gridBlankSize.x),
                     this->from.y + lineWidth + gridLocationFrom.y * (lineWidth + gridBlankSize.y)};

    POINT OUTto = {this->from.x + lineWidth + gridBlankSize.x - 1 + gridLocationTo.x * (lineWidth + gridBlankSize.x),
                   this->from.y + lineWidth + gridBlankSize.y - 1 + gridLocationTo.y * (lineWidth + gridBlankSize.y)};

    from = OUTfrom;
    to = OUTto;

    return;
}

POINT board::getGridLocation(POINT location) {
    POINT OUTfrom = {this->from.x + lineWidth + location.x * (lineWidth + gridBlankSize.x),
                     this->from.y + lineWidth + location.y * (lineWidth + gridBlankSize.y)};

    return OUTfrom;
}

bool board::addWord(word* word, POINT wordHeadLocation) {
    if (wordHeadLocation.x < 0 || wordHeadLocation.x + word->length - 1 > grid.x || wordHeadLocation.y < 0) {
        return false;
    }

    wordBlock* newWordBlock = new wordBlock{word, wordHeadLocation};
    this->wordVault.push_back(newWordBlock);
    for (int i = 0; i < word->length; i++) {
        this->WordInBoard[wordHeadLocation.x + i][wordHeadLocation.y] = newWordBlock;
    }
    return true;
}

word* board::getWord(POINT location) {
    if (bool(WordInBoard[location.x][location.y])) {
        return WordInBoard[location.x][location.y]->word;
    }
    return NULL;
}

void board::delWord(POINT location) {
    wordBlock* delword = WordInBoard[location.x][location.y];
    for (int i = 0; i < delword->word->length; i++) {
        this->WordInBoard[delword->headLocation.x + i][delword->headLocation.y] = NULL;
    }

    for (auto iter = this->wordVault.begin(); iter != this->wordVault.end(); iter++) {
        if ((*iter) == delword) {
            this->wordVault.erase(iter);
            break;
        }
    }
    return;
}

void board::removeBlock() {
    for (int i = 0; i < grid.x; i++) {
        for (int j = 0; j < grid.y; j++) {
            BlockedGrid[i][j] = 0;
        }
    }
    blocked = 0;
    return;
}

void board::render() const {
    fillrectangle(this->from.x, this->from.y, this->to.x, this->to.y);
    // X line
    for (int i = 0; i <= grid.x; i++) {
        line(this->from.x + i * (this->gridBlankSize.x + this->lineWidth), this->from.y,
             this->from.x + i * (this->gridBlankSize.x + this->lineWidth), this->to.y);
    }
    // Y line
    for (int i = 0; i <= grid.y; i++) {
        line(this->from.x, this->from.y + i * (this->gridBlankSize.y + this->lineWidth), this->to.x,
             this->from.y + i * (this->gridBlankSize.y + this->lineWidth));
    }

    // draw wordBlock
    for (auto iter = this->wordVault.begin(); iter != this->wordVault.end(); iter++) {
        int textLength = (*iter)->word->length;
        POINT from, to;
        this->getGridLocation(from, to, (*iter)->headLocation,
                              POINT{(*iter)->headLocation.x + textLength - 1, (*iter)->headLocation.y});
        clearrectangle(from.x, from.y, to.x, to.y);
        (*iter)->word->render({from.x - 1, from.y - 1}, {to.x - 1, to.y - 1});
    }

    // draw blocked grid
    for (int i = 0; i < grid.x; i++) {
        for (int j = 0; j < grid.y; j++) {
            if (BlockedGrid[i][j] == 1) {
                POINT from, to;
                this->getGridLocation(from, to, {i, j});
                line(from.x, from.y, to.x, to.y);
                line(from.x, to.y, to.x, from.y);
            }
        }
    }

    // draw player
    this->player->render();

    // HP render
    fillrectangle(from.x, ((windowSize::Y - 40 - 45) - to.y - 40) / 2 + to.y, to.x,
                  ((windowSize::Y - 40 - 45) - to.y - 40) / 2 + to.y + 40);

    for (int i = 1; i <= this->player->property[role::HealthPoint]; i++) {
        activity::drawPngAlpha(to.x - 36 * i, ((windowSize::Y - 40 - 45) - to.y - 40) / 2 + to.y + 4, (IMAGE*)&HP);
    }

    return;
}