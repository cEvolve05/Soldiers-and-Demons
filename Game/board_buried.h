#pragma once
#include <graphics.h>

/*
include boardSize, gridSize, origin
*/
class board
{
public:
	board();
	~board();

		//size{4,5} meaning 4*5 board
	void setBoardSize(POINT size);

		//meaning blank size
	void setGridSize(POINT size);
	void setBoardLocation(POINT location);

	void render();

private:
	POINT boardSize;
	POINT gridSize;
	POINT boardLocation;

	//const lineStyle
};

board::board()
{
	this->boardSize = { 0 };
	this->gridSize = { 0 };
	this->boardLocation = { 0 };
}

board::~board()
{
}

inline void board::setBoardSize(POINT size)
{
	boardSize = size;
	return;
}

inline void board::setGridSize(POINT size)
{
	gridSize = size;
	return;
}

inline void board::setBoardLocation(POINT location)
{
	boardLocation = location;
	return;
}

inline void board::render()
{
	LINESTYLE pstyle;
	getlinestyle(&pstyle);
	DWORD lineWidth = pstyle.thickness;
	//boardLocation.x, boardLocation.y
	//gridSize.x* boardSize.x+lineWidth*(boardSize.x+1), gridSize.y * boardSize.y + lineWidth * (boardSize.y + 1)
	//line(boardLocation.x,boardLocation.y,gridSize.x* boardSize.x+pstyle.thickness*(boardSize.x+1), gridSize.y * boardSize.y + pstyle.thickness * (boardSize.y + 1));

	DWORD x1,y1,x2,y2;
	//X line
	for (int i = 0; i <= boardSize.x; i++)
	{
		x1 = boardLocation.x;
		y1 = boardLocation.y + i * (lineWidth + gridSize.y);
		x2 = boardLocation.x + boardSize.x * (lineWidth + gridSize.x);
		y2 = y1;
		line(x1, y1, x2, y2);
	}
	//Y line
	for (int i = 0; i <= boardSize.x; i++)
	{
		x1 = boardLocation.x + i * (lineWidth + gridSize.x);
		y1 = boardLocation.y;
		x2 = x1;
		y2 = boardLocation.y + boardSize.y * (lineWidth + gridSize.y);
		line(x1, y1, x2, y2);
	}
}

