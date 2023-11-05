#include "include.h"

void GamingActivity::init()
{
	BeginBatchDraw();
	this->m = { 0 };
	L = new board;
	Lbox = new textBox;
	L->setBoardLocation({ 40,40 }, { 440,440 });
	L->setGrid({ 10,10 });
	L->init(L"./Resource/player.png");
	Lbox->setLocation({ 40,530 }, { 440,575 });

	setfillcolor(WHITE);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	return;
}

void GamingActivity::end()
{
	delete L;
	delete Lbox;
	EndBatchDraw();
	return;
}

void GamingActivity::lifeCycle()
{
	//loop inside
	//code for Gaming
	cleardevice();
	IMAGE img;
	loadimage(&img, L"./Resource/GamingUI.png", 0, 0);
	putimage(0, 0, &img);
	wchar_t arr[] = L"主菜单";
	button(457, 536, 457 + 110, 536 + 40, arr);
	init();
	L->addWord(new word{ L"魔王",2 ,word::Subject }, { 0,0 });
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
	//std::cout << "process" << std::endl;
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
		case VK_UP:
			//Right Role Move Up
			break;
		case VK_LEFT:
			//Right Role Move Left
			break;
		case VK_DOWN:
			//Right Role Move Down
			break;
		case VK_RIGHT:
			//Right Role Move Right
			break;
		case 'F':
			//Left Role get word
			Lbox->addWord(L->getWord(L->playerLocation));
			L->delWord(L->playerLocation);
			break;
		case 'E':
			//erase textBox
			Lbox->empty();
			break;
		case '0':
			//Right Role get word
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
	return;
}

void GamingActivity::render()
{
	//std::cout << "render" << std::endl;
	L->render();
	Lbox->render();
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
	settextstyle(to.y - from.y - 4, (to.y - from.y - 4) / length, L"黑体");
	//if (textwidth((LPCTSTR)text.c_str()) > length)
	//{
	//	std::cout << "text too long" << std::endl;
	//}
	outtextxy(from.x + 2, from.y + 2, (LPCTSTR)text.c_str());
}

wordProcess::wordProcess()
{
	//constructor
	this->data = new word * [5]
	{
		//Subject
		new word[2]
		{
			{L"勇者",2,word::Subject},
			{L"魔王",2,word::Subject},
		},

		//Verb
		new word[2]
		{
			{L"使用",2,word::Verb},
			//{L"进行",0,word::Verb},
			//{L"释放",0,word::Verb},
			{L"使出",2,word::Verb},
		},

		//Object
		new word[2]
		{
			{L"食物",2,word::Object},
			{L"药剂",2,word::Object},
		},

		//Action
		new word[3]
		{
			{L"攻击",2,word::Action},
			{L"强力攻击",4,word::Action},
			{L"防御",2,word::Action},
		},

		//Special
		new word[4]
		{
			{L"清空文本框",5,word::Special},
			{L"移除词块",4,word::Special},
			{L"生成词块",4,word::Special},
			{L"禁用棋盘",4,word::Special},
		},
	};
	
	for (int i = 0; i < 5; i++)
	{
		this->size[i] = sizeof(data[i])/sizeof(word);
	}

}

wordProcess::~wordProcess()
{
	//destructor
	for (int i = 0; i < 5; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}

void wordProcess::generateWord(board* targetBoard)
{
	// word type
	static int targetType = rand()%5;
	// word detail
	static int wordIndex = rand() % size[targetType];

	// word location
	static board::wordBlock*** boardStatue = targetBoard->WordInBoard;
	int wordSize = data[targetType][wordIndex].length;
	static int count,cycle=-1;
	static POINT headLocation;
	do
	{
		count = 0;
		cycle += 1;
		headLocation={ rand() % targetBoard->grid.x,rand() % targetBoard->grid.y };
		for (int i = 0; i < wordSize; i++)
		{
			count += bool(boardStatue[headLocation.x][headLocation.y]);
		}
		
	} while (count == 0 || cycle >= 10);

	targetBoard->addWord(new word{ data[targetType][wordIndex] }, headLocation);
	return;
}

void applySentence(textBox* targetTextBox)
{

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

void board::init(LPCTSTR pImgFile)
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

	// init role
	this->player->setImg(pImgFile, { gridBlankSize.x - 2, gridBlankSize.y - 2 });
	this->setPlayerLocation({ 0,0 });

	return;
}

void board::setPlayerLocation(POINT location)
{
	if (location.x<0 || location.y <0 || location.x > this->grid.x - 1 || location.y > this->grid.y - 1)
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

void board::addWord(word* word, POINT wordHeadLocation)
{
	wordBlock* newWordBlock = new wordBlock{ word,wordHeadLocation };
	this->wordVault.push_back(newWordBlock);
	for (int i = 0; i < word->length; i++)
	{
		this->WordInBoard[wordHeadLocation.x + i][wordHeadLocation.y] = newWordBlock;
	}
	return;
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

	this->player->render();
	return;
}

//-------------------------------------------------------------------------------
//class role

role::role()
{
	this->health = 5;
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

void role::render()
{
	putimage(this->location.x, this->location.y, &this->img);
	return;
}