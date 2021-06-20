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
	//�󶨾������
	void bindSprite(Sprite* sprite);
	Sprite* getSprite();

	//���ÿ�����
	void setController(mController* controller);

	//ʵ��simplemovelistener�ӿڵķ���
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();

	void setTiledMap(TMXTiledMap* map);

	//����������ת��Ϊ��ͼ��������
	Point tileCoordForPosition(Point pos);

protected:
	Sprite* m_sprite;
	mController* m_controller;
	TMXTiledMap* m_map;
	//�����ײ�ĵ�ͼ��
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