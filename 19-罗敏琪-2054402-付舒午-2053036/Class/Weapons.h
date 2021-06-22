#pragma once
#ifndef __INCLUDE_Weapons_H__
#define __INCLUDE_Weapons_H__
//#include "cocos2d.h"
#include "Characters.h"
//#include "Player.h"
//using namespace cocos2d;
#include<iostream>

using namespace std;


class Weapons :public Characters {
public:
	
	Weapons();
	~Weapons();
	CREATE_FUNC(Weapons);

	virtual bool init();

	virtual void update(float dt);

	bool isAttack();

	Point getTarget_pos();

	void setDirection(Point aim);

	void fireAnimation();

	void setType(string type);
	string getType();

protected:
	Point weaponPosition;

	bool ifLaunch;

	string Type;
};

#endif