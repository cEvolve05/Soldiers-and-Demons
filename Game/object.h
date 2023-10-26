#pragma once
#include <graphics.h>

// object include role, words, efforts.
class object
{
public:
	object();
	object(POINT location, LPCTSTR pResType, LPCTSTR pResName);
	object(POINT location, LPCTSTR pImgFile);
	~object();

	enum XorY
	{
		X,
		Y
	};

	void setLocation(POINT location);
	LONG getLocation(XorY choose) const;
	void shiftLocation(POINT shiftValue);

	// get img from resource
	void setImg(LPCTSTR pResType, LPCTSTR pResName);
	void setImg(LPCTSTR pImgFile);

	virtual void render();

protected:
	// left-top point
	POINT objectLocation;
	IMAGE objectImg;

	//0 as lowest layer,render first;the bigger, the later
	//bg=0,board=1,HUD=1,word=2,effortL=3,player=4,effortH=5
	//int renderLevel;
};

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

inline object::object(POINT location, LPCTSTR pImgFile)
{
	objectLocation = location;
	setImg(pImgFile);
}

object::~object()
{
}

inline void object::setLocation(POINT location)
{
	objectLocation = location;
	return;
}

inline LONG object::getLocation(XorY choose) const
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

inline void object::shiftLocation(POINT shiftValue)
{
	objectLocation.x += shiftValue.x;
	objectLocation.y += shiftValue.y;
	return;
}

inline void object::setImg(LPCTSTR pResType, LPCTSTR pResName)
{
	loadimage(&objectImg, pResType, pResName);
	return;
}

inline void object::setImg(LPCTSTR pImgFile)
{
	loadimage(&objectImg, pImgFile);
	return;
}

inline void object::render()
{
	putimage(objectLocation.x, objectLocation.y, &objectImg);
}

class role final: public object
{
public:
	/*struct roleData
	{
		int attack; //attack
		int magicAttack; //magic attack
		int healthPoints; //health points
		int recovery;
		int speed;
	}roleOriginData, roleCurrentData;*/

	role();
	//role(POINT location, LPCTSTR pResType, LPCTSTR pResName, roleData INdata);
	role(POINT location, LPCTSTR pResType, LPCTSTR pResName);

private:

};

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

class board final: protected object
{
public:
	//size{4,5} meaning 4*5 board
	void setBoardSize(POINT size);

	//meaning blank size
	void setGridSize(POINT size);
	void render() override;
private:
	POINT boardSize;
	POINT gridSize;
	POINT boardLocation;
};

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

inline void board::render()
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
}