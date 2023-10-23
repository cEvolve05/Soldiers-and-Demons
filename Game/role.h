#pragma once
#include <graphics.h>

// role is to store data of a role and show it
class role
{
public:
	role();
	~role();
	struct roleData
	{
		int attack; //attack
		int magicAttack; //magic attack
		int healthPoints; //health points
		int recovery;
		int speed;
	};

	void setLocation(POINT location);
	LONG getLocation(char XorY);
	void shiftLocation(char XorY, int shiftValue);
	
	// get img from resource
	void setRoleImg(LPCTSTR pResType, LPCTSTR pResName);

	// show role in location
	//type = 0: Normal, no alpha channel
	//       1: Transparent, low prefermance TO-DO
	void render(int type=0);

private:
	// left-upper point
	POINT roleLocation;
	IMAGE roleImg;
};

role::role()
{
	this->roleLocation = { 0,0 };
}

role::~role()
{
}

inline void role::setLocation(POINT location)
{
	roleLocation = location;
	return;
}

inline LONG role::getLocation(char XorY)
{
	switch (XorY)
	{
		case 'X':
			return roleLocation.x;
		case 'Y':
			return roleLocation.y;
	}
	return 0;
}

inline void role::shiftLocation(char XorY, int shiftValue)
{
	switch (XorY)
	{
	case 'X':
		roleLocation.x += shiftValue;
		return;
	case 'Y':
		roleLocation.y += shiftValue;
		return;
	}
	return;
}

inline void role::setRoleImg(LPCTSTR pResType, LPCTSTR pResName)
{
	loadimage(&roleImg, pResType, pResName);
	return;
}

inline void role::render(int type)
{
	switch (type)
	{
	default:
	case 0:
		putimage(roleLocation.x, roleLocation.y, &roleImg);
		break;
	}
	return;
}