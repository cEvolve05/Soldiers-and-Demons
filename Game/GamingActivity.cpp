#include "include.h"

void GamingActivity::init()
{
	BeginBatchDraw();
	this->m = { 0 };


	L = new board;
	L->setBoardLocation({ 40,40 }, { 40 + 411,40 + 411 });
	L->setGrid({ 10,10 });
	L->init();
	L->player->label = L"勇者";
	L->player->setImg(L"./Resource/Soldier.png", L->gridBlankSize);
	L->sentence->setLocation({ 40,windowSize::Y - 40 - 45 }, { 40 + 411,windowSize::Y - 40 });

	R = new board;
	R->setBoardLocation({ windowSize::X - 40 - 411,40 }, { windowSize::X - 40,40 + 411 });
	R->setGrid({ 10,10 });
	R->init();
	R->player->label = L"魔王";
	R->player->setImg(L"./Resource/Demon.png", R->gridBlankSize);
	R->sentence->setLocation({ windowSize::X - 40 - 411,windowSize::Y - 40 - 45 }, { windowSize::X - 40,windowSize::Y - 40 });

	wordProc = new wordProcess;

	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	return;
}

void GamingActivity::end()
{
	delete L, R;
	EndBatchDraw();
	return;
}

void GamingActivity::lifeCycle()
{
	//loop inside
	//code for Gaming
	cleardevice();
	button(457, 536, 457 + 110, 536 + 40, (wchar_t*)L"主菜单");
	init();
	//L->addWord(new word{ L"魔王",2 ,word::Subject }, { 0,0 });
	for (int i = 0; i < 5; i++)
	{
		wordProc->generateWord(L);
		wordProc->generateWord(R);
	}

	while (game::getRunningStatus() && !exitActivity)
	{
		//std::cout << "cycle start" << std::endl;
		inputFilter();
		process();
		render();
		Sleep(8);
	}
	end();
	return;
}

void GamingActivity::inputFilter()
{
	//std::cout << "inputFilter" << std::endl;
	//flushmessage(EX_MOUSE | EX_CHAR);
	//Input Process
	while (peekmessage(&m, EX_MOUSE | EX_KEY | EX_WINDOW))
	{
		switch (m.message)
		{
		case WM_LBUTTONDOWN:
			if (m.x >= 457 && m.x <= 457 + 110 && m.y >= 536 && m.y <= 536 + 40)
			{
				activityManager::setActivity(new MenuActivity);
				exitActivity = 1;
				return;
			}
			break;
		case WM_MOUSEMOVE:
			//putpixel(m.x, m.y, RED);
			break;

		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
			{
				game::setRunningStatus(0);
				return;
			}
			if (m.prevdown == 0)
			{
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
	return;
}

void GamingActivity::process()
{
	//input process
	while (input.empty() == 0)
	{
		switch (input.front())
		{

		case 'W':
			//Left Role Move Up
			this->L->setPlayerLocation({ this->L->playerLocation.x,this->L->playerLocation.y - 1 });
			break;
		case 'A':
			//Left Role Move Left
			this->L->setPlayerLocation({ this->L->playerLocation.x - 1,this->L->playerLocation.y });
			break;
		case 'S':
			//Left Role Move Down
			this->L->setPlayerLocation({ this->L->playerLocation.x,this->L->playerLocation.y + 1 });
			break;
		case 'D':
			//Left Role Move Right
			this->L->setPlayerLocation({ this->L->playerLocation.x + 1,this->L->playerLocation.y });
			break;
		case 'F':
			//Left Role get word
			L->sentence->addWord(L->getWord(L->playerLocation));
			L->delWord(L->playerLocation);
			break;
		case 'E':
			//erase textBox
			L->sentence->empty();
			break;
		case 'R':
			//apply sentence
			wordProc->applySentence(L, R);
			break;



		case 'U':
			//Right Role Move Up
			this->R->setPlayerLocation({ this->R->playerLocation.x,this->R->playerLocation.y - 1 });
			break;
		case 'H':
			//Right Role Move Left
			this->R->setPlayerLocation({ this->R->playerLocation.x - 1,this->R->playerLocation.y });
			break;
		case 'J':
			//Right Role Move Down
			this->R->setPlayerLocation({ this->R->playerLocation.x,this->R->playerLocation.y + 1 });
			break;
		case 'K':
			//Right Role Move Right
			this->R->setPlayerLocation({ this->R->playerLocation.x + 1,this->R->playerLocation.y });
			break;
		case 'L':
			//Right Role get word
			R->sentence->addWord(R->getWord(R->playerLocation));
			R->delWord(R->playerLocation);
			break;
		case 'I':
			//erase textBox
			R->sentence->empty();
			break;
		case 'O':
			//apply sentence
			wordProc->applySentence(R, L);
			break;


		case 'C':
			wordProc->DEBUGremoveBlock(L);
			break;
		case 'V':
			wordProc->DEBUGremoveBlock(R);
			break;
		case VK_ESCAPE:
			//Exit Game
			activityManager::setActivity(new MenuActivity);
			exitActivity = 1;
			EndBatchDraw();
			return;
			break;
		}
		input.pop();
	}

	using namespace std::chrono;

	//generate word
	static auto generateTimer = steady_clock::now();
	if (duration_cast<milliseconds>(steady_clock::now() - generateTimer).count() > 200)
	{
		generateTimer = steady_clock::now();
		wordProc->generateWord(L);
		wordProc->generateWord(R);
	}


	if (L->blocked == 1 && duration_cast<seconds>(steady_clock::now() - L->removeBlockTimer).count() > 5)
	{
		L->removeBlock();
	}
	if (R->blocked == 1 && duration_cast<seconds>(steady_clock::now() - R->removeBlockTimer).count() > 5)
	{
		R->removeBlock();
	}
	//L->player->property[role::HealthPoint] -= 1;

	return;
}

void GamingActivity::render()
{
	//std::cout << "render" << std::endl;

	if (L->player->property[role::HealthPoint] < 1 || R->player->property[role::HealthPoint] < 1)
	{
		std::wcout << L"勇者血量：" << L->player->property[role::HealthPoint] << std::endl;
		std::wcout << L"魔王血量：" << R->player->property[role::HealthPoint] << std::endl;



		POINT from{ windowSize::X / 2 * 0.382,windowSize::Y / 2 * 0.382 }, to{ windowSize::X / 2 * 1.618,windowSize::Y / 2 * 1.618 };

		IMAGE img;
		loadimage(&img, L"./Resource/Background.jpg", 0, 0);
		putimage(0, 0, &img);
		fillrectangle(from.x, from.y, to.x, to.y);

		std::wstring text = std::format(L"{}胜利", L->player->property[role::HealthPoint] > R->player->property[role::HealthPoint] ? L"勇者" : L"魔王");
		std::wstring text2 = std::format(L"勇者血量：{}    魔王血量：{}", L->player->property[role::HealthPoint], R->player->property[role::HealthPoint]);

		outtextxy((to.x - from.x - textwidth(text.c_str())) / 2 + from.x, (to.y - from.y - textheight(text.c_str())) / 2 + from.y - textheight(text2.c_str()), (LPCTSTR)text.c_str());
		outtextxy((to.x - from.x - textwidth(text2.c_str())) / 2 + from.x, (to.y - from.y - textheight(text2.c_str())) / 2 + from.y, (LPCTSTR)text2.c_str());


		button(457, 536, 457 + 110, 536 + 40, (wchar_t*)L"主菜单");
		FlushBatchDraw();
		while (true)
		{
			getmessage(&m, EX_MOUSE);
			if (m.message == WM_LBUTTONDOWN && m.x >= 457 && m.x <= 457 + 110 && m.y >= 536 && m.y <= 536 + 40)
			{
				activityManager::setActivity(new MenuActivity);
				exitActivity = 1;
				return;
			}
		}
		return;
	}

	IMAGE img;
	loadimage(&img, L"./Resource/Background.jpg", 0, 0);
	putimage(0, 0, &img);
	L->render();
	L->sentence->render();
	R->render();
	R->sentence->render();
	button(457, 536, 457 + 110, 536 + 40, (wchar_t*)L"主菜单");
	FlushBatchDraw();
	return;
}

//-------------------------------------------------------------------------------
//class TextBox

textBox::textBox()
{
	//constructor
	this->from = { 0,0 };
	this->to = { 0,0 };
	//addWord(new word{ L"我",1,0 });
}

textBox::~textBox()
{
	//destructor
	words.clear();
	for (auto iter = words.begin(); iter != words.end(); iter++)
	{
		delete (*iter);
	}
}

void textBox::addWord(word* INword)
{
	//add word to the word list
	this->words.push_back(INword);
	return;
}

void textBox::empty()
{
	//empty the word list
	this->words.clear();
	return;
}

void textBox::setLocation(POINT from, POINT to)
{
	//set the size of the text box
	this->from = from;
	this->to = to;
	return;
}

void textBox::render()
{
	//clearrectangle(from.x, from.y, to.x, to.y);
	fillrectangle(from.x, from.y, to.x, to.y);

	int y1 = from.y + 2, y2 = to.y - 2, x1 = from.x + 2;
	settextstyle(y2 - y1 - 4, 0, L"黑体");
	for (auto iter = words.begin(); iter != words.end(); iter++)
	{
		fillrectangle(x1, y1, x1 + textwidth((*iter)->text.c_str()) + 2, y2);
		outtextxy(x1 + 2, y1 + 2, (LPCTSTR)(*iter)->text.c_str());
		x1 = x1 + textwidth((*iter)->text.c_str()) + 2 + 2;
	}
	return;
}

//-------------------------------------------------------------------------------
//class word and processor

word::word(std::wstring text, int length, wordType type)
{
	this->text = text;
	if (length == 0)
	{
		this->length = text.size();
	}
	else
	{
		this->length = length;
	}
	this->type = type;
}

void word::render(POINT from, POINT to)
{
	fillrectangle(from.x, from.y, to.x, to.y);
	settextstyle(to.y - from.y - 4, 0, L"黑体");
	//if (textwidth((LPCTSTR)text.c_str()) > length)
	//{
	//	std::cout << "text too long" << std::endl;
	//}
	outtextxy((to.x - from.x - textwidth(this->text.c_str())) / 2 + from.x, (to.y - from.y - textheight(this->text.c_str())) / 2 + from.y, (LPCTSTR)text.c_str());
}

wordProcess::wordProcess()
{
	//constructor

	//data
	{
		//Subject
		this->data.push_back
		({
				{{L"勇者",2,word::Subject},1},
				{{L"魔王",2,word::Subject},1},
		});

		//Verb
		this->data.push_back
		({
				{{L"使用",2,word::Verb},1},
				//{{L"进行",0,word::Verb},1},
				//{{L"释放",0,word::Verb},1},
				{{L"使出",2,word::Verb},2},
		});

		//Object
		this->data.push_back
		({
				{{L"食物",2,word::Item},2},
				{{L"药剂",2,word::Item},1},
		});

		//Action
		this->data.push_back
		({
				{{L"攻击",2,word::Action},2},
				{{L"强力攻击",4,word::Action},1},
				//{{L"防御",2,word::Action},1},
		});

		//Special
		this->data.push_back
		({
				{{L"清空文本框",5,word::Special},1},
				{{L"移除词块",4,word::Special},1},
				{{L"生成词块",4,word::Special},1},
				{{L"禁用棋盘",4,word::Special},1},
		});
	}

	//data size
	{
		this->size.reserve(word::wordType::COUNT);
		for (int i = 0; i < word::wordType::COUNT; i++)
		{
			this->size.push_back(data[i].size());
		}
	}

	//type possibility
	{
		int typePossibilityRatio[word::wordType::COUNT]{ 3,3,1,1,1 };
		this->typePossibility.reserve(word::wordType::COUNT);
		int typePossibilitySum = 0;
		for (int i = 0; i < word::wordType::COUNT; i++)
		{
			typePossibilitySum += typePossibilityRatio[i];
		}
		for (int i = 0; i < word::wordType::COUNT; i++)
		{
			this->typePossibility.push_back(double(typePossibilityRatio[i]) / double(typePossibilitySum));
		}
	}

	//word possibility
	{
		//allocate
		this->wordPossibility.reserve(word::wordType::COUNT);
		for (int i = 0; i < word::wordType::COUNT; i++)
		{
			wordPossibility.push_back(std::vector<double>(size[i]));
		}

		int wordPossibilitySum[word::wordType::COUNT] = { 0 };
		for (int i = 0; i < word::wordType::COUNT; i++)
		{
			for (int j = 0; j < size[i]; j++)
			{
				wordPossibilitySum[i] += data[i][j].possibility;
			}
			std::cout << std::endl;
		}
		for (int i = 0; i < word::wordType::COUNT; i++)
		{
			for (int j = 0; j < size[i]; j++)
			{
				wordPossibility[i][j]=double(data[i][j].possibility) / double(wordPossibilitySum[i]);
			}
		}
	}

	//for (int i = 0; i < 5; i++)
	//{
	//	this->size[i] = sizeof(data[i]) / sizeof(word);
	//}

}

wordProcess::~wordProcess()
{
	//destructor
}

void wordProcess::generateWord(board* targetBoard)
{
	double random;

	// word type
	int targetType = rand() % 5;
	random = double(rand()) / double(RAND_MAX);
	for (int i = 0; i < word::wordType::COUNT; i++)
	{
		random -= typePossibility[i];
		if (random < 0.0)
		{
			targetType = i;
			break;
		}
	}

	// word detail
	int wordIndex = rand() % size[targetType];
	random = double(rand()) / double(RAND_MAX);
	for (int i = 0; i < size[targetType]; i++)
	{
		random -= wordPossibility[targetType][i];
		if (random < 0.0)
		{
			wordIndex = i;
			break;
		}
	}

	// word location
	board::wordBlock*** boardStatue = targetBoard->WordInBoard;




	int wordSize = data[targetType][wordIndex].word.length;
	int count = 0;
	POINT headLocation;
	for (int i = 0; i < 5; i++)
	{
		headLocation =
		{
			rand() % (targetBoard->grid.x - (wordSize - 1)),
			rand() % targetBoard->grid.y
		};
		for (int i = 0; i < wordSize; i++)
		{
			count += bool(boardStatue[headLocation.x + i][headLocation.y]);
		}
		if (count == 0)
		{
			if (targetType == word::Subject)
			{
				word* tmp = new word{ data[targetType][wordIndex].word };
				tmp->text = targetBoard->player->label;
				targetBoard->addWord(tmp, headLocation);
				break;
			}
			targetBoard->addWord(new word{ data[targetType][wordIndex].word }, headLocation);
			break;
		}
	}
	return;
}

bool wordProcess::applySentence(board* from, board* to)
{
	std::vector<word*>& sentence = from->sentence->words;

	if (sentence.size() != 3)
	{
		from->sentence->empty();
		return false;
	}

	if (sentence[0]->text != from->player->label || sentence[1]->type != word::Verb)
	{
		from->sentence->empty();
		return false;
	}

	if ((sentence[1]->text == L"使用" && sentence[2]->type != word::Item) ||
		(sentence[1]->text == L"使出" && sentence[2]->type == word::Item))
	{
		from->sentence->empty();
		return false;
	}

	if (sentence[1]->text == L"使用")
	{
		useItem(sentence[2], from, to);
	}
	else if (sentence[1]->text == L"使出")
	{
		makeAction(sentence[2], from, to);
	}
	from->sentence->empty();
	return true;
}

void wordProcess::useItem(word* item, board* from, board* to)
{
	if (item->text == L"食物")
	{
		from->player->shiftProerty(role::HealthPoint, +1);
	}
	else if (item->text == L"药剂")
	{
		from->player->shiftProerty(role::HealthPoint, +2);
	}

	return;
}

void wordProcess::makeAction(word* item, board* from, board* to)
{
	// Action
	if (item->text == L"攻击")
	{
		to->player->shiftProerty(role::HealthPoint, -1);
	}
	else if (item->text == L"强力攻击")
	{
		to->player->shiftProerty(role::HealthPoint, -2);
	}
	else if (item->text == L"防御")
	{
		from->player->shiftProerty(role::Defence, -1);
	}
	// Special
	else if (item->text == L"清空文本框")
	{
		to->sentence->empty();
	}
	else if (item->text == L"移除词块")
	{
		removeBlock(to);
	}
	else if (item->text == L"生成词块")
	{
		for (int i = 0; i < 5; i++)
		{
			generateWord(from);
		}
	}
	else if (item->text == L"禁用棋盘")
	{
		blockBoard(to);
	}

	return;
}

void wordProcess::removeBlock(board* target)
{
	int cycleTime = target->wordVault.size() * 0.5;// decide % to remove
	for (int i = 0; i < cycleTime; i++)
	{
		target->delWord(target->wordVault[rand() % target->wordVault.size()]->headLocation);
	}
	return;
}

void wordProcess::DEBUGremoveBlock(board* target)
{
	for (int i = 0; i < target->wordVault.size(); i++)
	{
		target->delWord(target->wordVault[0]->headLocation);
	}
	return;
}

void wordProcess::blockBoard(board* target)
{
	int cycleTime = target->grid.x * target->grid.y * 0.3;// decide % to block
	for (int i = 0; i < cycleTime; i++)
	{
		POINT location =
		{
			rand() % target->grid.x,
			rand() % target->grid.y
		};
		if (target->BlockedGrid[location.x][location.y] == 0)
		{
			target->BlockedGrid[location.x][location.y] = 1;
		}
		else
		{
			i--;
		}
	}

	target->removeBlockTimer = std::chrono::steady_clock::now();
	target->blocked = 1;
	return;
}


//-------------------------------------------------------------------------------
//class board


board::board()
{
	this->grid = { 0 };
	this->from = { 0 };
	this->to = { 0 };
	this->WordInBoard = NULL;
	this->lineWidth = { 0 };
	this->gridBlankSize = { 0 };
	this->player = new role;
	this->playerLocation = { 0 };
	this->sentence = new textBox;
	this->BlockedGrid = { 0 };
}

board::~board()
{
	//destructor
	for (auto iter = this->wordVault.begin(); iter != this->wordVault.end(); iter++)
	{
		delete (*iter);
	}

	for (int i = 0; i < this->grid.x; i++)
	{
		delete this->WordInBoard[i];
	}
	delete this->WordInBoard;

	wordVault.clear();

	delete player;
	delete sentence;
}

void board::setBoardLocation(POINT from, POINT to)
{
	this->from = from;
	this->to = to;
	return;
}

void board::setGrid(POINT grid)
{
	this->grid = grid;
	return;
}

void board::init()
{
	LINESTYLE pstyle;
	getlinestyle(&pstyle);
	this->lineWidth = pstyle.thickness;

	POINT gridBlankSize =
	{
		(this->to.x - this->from.x + 1 - lineWidth * (grid.x + 1)) / grid.x,
		(this->to.y - this->from.y + 1 - lineWidth * (grid.y + 1)) / grid.y
	};
	this->gridBlankSize = gridBlankSize;

	// init WordInBoard
	this->WordInBoard = new wordBlock * *[grid.x];
	for (int i = 0; i < grid.x; i++)
	{
		WordInBoard[i] = (new wordBlock * [grid.y] {NULL});
	}

	this->BlockedGrid = new int* [grid.x];
	for (int i = 0; i < grid.x; i++)
	{
		BlockedGrid[i] = (new int [grid.y] {0});
	}

	// init role
	this->setPlayerLocation({ 0,0 });

	return;
}

void board::setPlayerLocation(POINT location)
{
	if (location.x<0 || location.y <0 || location.x > this->grid.x - 1 || location.y > this->grid.y - 1 || BlockedGrid[location.x][location.y] == 1)
	{
		return;
	}
	this->playerLocation = location;
	POINT tmp = getGridLocation(location);
	this->player->setLocation({ tmp.x + 1,tmp.y + 1 });
	return;
}

void board::getGridLocation(POINT& from, POINT& to, POINT gridLocationFrom, POINT gridLocationTo) const
{
	if (gridLocationTo.x == -1 && gridLocationTo.y == -1)
	{
		gridLocationTo = gridLocationFrom;
	}

	POINT OUTfrom =
	{
		this->from.x + lineWidth + gridLocationFrom.x * (lineWidth + gridBlankSize.x),
		this->from.y + lineWidth + gridLocationFrom.y * (lineWidth + gridBlankSize.y)
	};

	POINT OUTto =
	{
		this->from.x + lineWidth + gridBlankSize.x - 1 + gridLocationTo.x * (lineWidth + gridBlankSize.x),
		this->from.y + lineWidth + gridBlankSize.y - 1 + gridLocationTo.y * (lineWidth + gridBlankSize.y)
	};

	from = OUTfrom;
	to = OUTto;

	return;
}

POINT board::getGridLocation(POINT location)
{
	POINT OUTfrom =
	{
		this->from.x + lineWidth + location.x * (lineWidth + gridBlankSize.x),
		this->from.y + lineWidth + location.y * (lineWidth + gridBlankSize.y)
	};

	return OUTfrom;
}

bool board::addWord(word* word, POINT wordHeadLocation)
{
	if (wordHeadLocation.x<0 ||
		wordHeadLocation.x + word->length - 1>grid.x ||
		wordHeadLocation.y < 0)
	{
		return false;
	}

	wordBlock* newWordBlock = new wordBlock{ word,wordHeadLocation };
	this->wordVault.push_back(newWordBlock);
	for (int i = 0; i < word->length; i++)
	{
		this->WordInBoard[wordHeadLocation.x + i][wordHeadLocation.y] = newWordBlock;
	}
	return true;
}

word* board::getWord(POINT location)
{
	return WordInBoard[location.x][location.y]->word;
}

void board::delWord(POINT location)
{
	wordBlock* delword = WordInBoard[location.x][location.y];
	for (int i = 0; i < delword->word->length; i++)
	{
		this->WordInBoard[delword->headLocation.x + i][delword->headLocation.y] = NULL;
	}

	for (auto iter = this->wordVault.begin(); iter != this->wordVault.end(); iter++)
	{
		if ((*iter) == delword)
		{
			this->wordVault.erase(iter);
			break;
		}
	}
	return;
}

void board::removeBlock()
{
	for (int i = 0; i < grid.x; i++)
	{
		for (int j = 0; j < grid.y; j++)
		{
			BlockedGrid[i][j] = 0;
		}
	}
	blocked = 0;
	return;
}

void board::render() const
{
	fillrectangle(this->from.x, this->from.y, this->to.x, this->to.y);
	//X line
	for (int i = 0; i <= grid.x; i++)
	{
		line(this->from.x + i * (this->gridBlankSize.x + this->lineWidth),
			this->from.y,
			this->from.x + i * (this->gridBlankSize.x + this->lineWidth),
			this->to.y);
	}
	//Y line
	for (int i = 0; i <= grid.y; i++)
	{
		line(this->from.x,
			this->from.y + i * (this->gridBlankSize.y + this->lineWidth),
			this->to.x,
			this->from.y + i * (this->gridBlankSize.y + this->lineWidth));
	}

	//draw wordBlock
	for (auto iter = this->wordVault.begin(); iter != this->wordVault.end(); iter++)
	{
		int textLength = (*iter)->word->length;
		POINT from, to;
		this->getGridLocation(from, to, (*iter)->headLocation, POINT { (*iter)->headLocation.x + textLength - 1, (*iter)->headLocation.y });
		clearrectangle(from.x, from.y, to.x, to.y);
		(*iter)->word->render({ from.x - 1,from.y - 1 }, { to.x - 1,to.y - 1 });
	}

	//draw blocked grid
	for (int i = 0; i < grid.x; i++)
	{
		for (int j = 0; j < grid.y; j++)
		{
			if (BlockedGrid[i][j] == 1)
			{
				POINT from, to;
				this->getGridLocation(from, to, { i,j });
				line(from.x, from.y, to.x, to.y);
				line(from.x, to.y, to.x, from.y);
			}
		}
	}

	//draw player
	this->player->render();

	//HP render
	IMAGE img;
	loadimage(&img, L"./Resource/HP.png", 0, 0);
	fillrectangle(from.x, ((windowSize::Y - 40 - 45) - to.y - 40) / 2 + to.y,
		to.x, ((windowSize::Y - 40 - 45) - to.y - 40) / 2 + to.y + 40);

	for (int i = 1; i <= this->player->property[role::HealthPoint]; i++)
	{
		activity::drawPngAlpha(to.x - 36 * i, ((windowSize::Y - 40 - 45) - to.y - 40) / 2 + to.y + 4, &img);
	}

	return;
}

//-------------------------------------------------------------------------------
//class role

role::role()
{
	this->property = new int[roleProperty::COUNT] {5, 0};
	this->MaxProperty = new const int[roleProperty::COUNT] {5, INT_MAX};
	this->location = { 0 };
}

void role::setLocation(POINT location)
{
	this->location = location;
	return;
}

void role::setImg(LPCTSTR pResType, LPCTSTR pResName, POINT size)
{
	loadimage(&this->img, pResType, pResName, size.x, size.y);
	return;
}

void role::setImg(LPCTSTR pImgFile, POINT size)
{
	loadimage(&this->img, pImgFile, size.x, size.y);
	return;
}

bool role::shiftProerty(roleProperty targetProperty, int shiftValue)
{
	if (property[targetProperty] + shiftValue > MaxProperty[targetProperty])
	{
		return false;
	}

	property[targetProperty] += shiftValue;

	return true;
}

void role::render()
{
	activity::drawPngAlpha(this->location.x, this->location.y, &this->img);
	return;
}