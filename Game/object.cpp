#include "include.h"

object::object()
{
	this->objectLocation = { 0 };
	this->objectImg = NULL;
}

object::object(POINT location, LPCTSTR pResType, LPCTSTR pResName)
{
	objectLocation = location;
	setImg(pResType, pResName);
}

object::object(POINT location, LPCTSTR pImgFile)
{
	objectLocation = location;
	setImg(pImgFile);
}

object::~object()
{
}

void object::setLocation(POINT location)
{
	objectLocation = location;
	return;
}

LONG object::getLocation(XorY choose) const
{
	switch (choose)
	{
	case X:
		return objectLocation.x;
	case Y:
		return objectLocation.y;
	}
	return 0;
}

void object::shiftLocation(POINT shiftValue)
{
	objectLocation.x += shiftValue.x;
	objectLocation.y += shiftValue.y;
	return;
}

void object::setImg(LPCTSTR pResType, LPCTSTR pResName)
{
	loadimage(&objectImg, pResType, pResName);
	return;
}

void object::setImg(LPCTSTR pImgFile)
{
	loadimage(&objectImg, pImgFile);
	return;
}

void object::render()
{
	putimage(objectLocation.x, objectLocation.y, &objectImg);
	return;
}

role::role()
{
	this->objectLocation = { 0 };
	this->objectImg = NULL;
	//this->roleOriginData = { 0 };
	//this->roleCurrentData = { 0 };
}

role::role(POINT location, LPCTSTR pResType, LPCTSTR pResName)
{
	setLocation(location);
	setImg(pResType, pResName);
	//this->roleOriginData = INdata;
	//this->roleCurrentData = INdata;
}

void board::setBoardSize(POINT size)
{
	boardSize = size;
	return;
}

void board::setGridSize(POINT size)
{
	gridSize = size;
	return;
}

void board::render()
{
	LINESTYLE pstyle;
	getlinestyle(&pstyle);
	DWORD lineWidth = pstyle.thickness;
	//boardLocation.x, boardLocation.y
	//gridSize.x* boardSize.x+lineWidth*(boardSize.x+1), gridSize.y * boardSize.y + lineWidth * (boardSize.y + 1)
	//line(boardLocation.x,boardLocation.y,gridSize.x* boardSize.x+pstyle.thickness*(boardSize.x+1), gridSize.y * boardSize.y + pstyle.thickness * (boardSize.y + 1));

	DWORD x1, y1, x2, y2;
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
	return;
}