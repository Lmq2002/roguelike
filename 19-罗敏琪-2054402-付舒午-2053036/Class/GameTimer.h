#pragma once
#ifndef _GAMETIMER_H_
#define _GAMETIMER_H_
#include "cocos2d.h"
using namespace cocos2d;
/*�����Ķ��������Ϊĳ�Զ���ڵ���ĳ�Ա�������������ڳ�ʼ��ĳһ�ڵ��ʱ����������*/
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
	/*���ʱ����ȷ��񣬻�����Ϸ����ʱ���֣���Ҫ�ڱ��ڵ��update�ϼ��룬�Ῠ������Ϊÿ0.01����Ⱦһ��̫����
	�����static����Ϊ���Թ�Ȼ���ʼ��һֱ�ǿ�ָ�룬����ò������*/
	cocos2d::Label* label;
	static float pTime;
private:
	
	
};
#endif

