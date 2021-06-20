#pragma once
#ifndef _GAMETIMER_H_
#define _GAMETIMER_H_
#include "cocos2d.h"
using namespace cocos2d;
/*这个类的对象可以作为某自定义节点类的成员变量，而不是在初始化某一节点的时候声明变量*/
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
	/*检测时间正确与否，或者游戏结算时出现，不要在本节点的update上加入，会卡死，因为每0.01秒渲染一次太多了
	不设成static是因为尝试过然后初始化一直是空指针，问题得不到解决*/
	cocos2d::Label* label;
	static float pTime;
private:
	
	
};
#endif

