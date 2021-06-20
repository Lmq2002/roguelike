#pragma once
#ifndef _Characters_H_
#define _Characters_H_

#include "cocos2d.h"
#include "Controller.h"
#include "controllerListener.h"
using namespace cocos2d;

class Characters :public Node, public controllerListener
{
public:
	//绑定精灵对象
	void bindSprite(Sprite* sprite);
	Sprite* getSprite();

	//设置控制器
	void setController(mController* controller);

	//实现simplemovelistener接口的方法
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();

	void setTiledMap(TMXTiledMap* map);

	//将像素坐标转换为地图格子坐标
	Point tileCoordForPosition(Point pos);

protected:
	Sprite* m_sprite;
	mController* m_controller;
	TMXTiledMap* m_map;
	//检测碰撞的地图层
	TMXLayer* meta;
	TMXLayer* wooden_case;
	//TMXLayer* barrier_fence_ice;

	clock_t  start_time;
	float nowTime;

	int time;
	int time_2;
	int time_3;
	int time_4;
	int time_5;
	int _time = 0;
	int record_time_defence;
	int record_time;

private:

};





#endif