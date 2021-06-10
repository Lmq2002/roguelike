#pragma once
#ifndef _GAMETIMER_H_
#define _GAMETIMER_H_
#include "cocos2d.h"
using namespace cocos2d;
class GameTimer:public cocos2d::Node
{
public:
	GameTimer();
	virtual ~GameTimer();
	static GameTimer* createTimer();
	void update(float dt);
	bool init();
	void stop();
	float getTime();
	//cocos2d::Label* label;
	//static cocos2d::MenuItemLabel* menuLabel;
	
private:
	static float pTime;
	
};
#endif

