#pragma once
#ifndef _REDBOTTLE_H_
#define _REDBOTTLE_H_
#include "cocos2d.h"
#include "Player.h"

using namespace cocos2d;



class RedBottle:
	public Node
{
public:
	CREATE_FUNC(RedBottle);
	static RedBottle* createRedBottle(bool redType);
	void update(float dt);
	void disperseAni();
	void bindPlayer(Player* player);
	bool allowFlying();
	void flyAni(Vec2 target);
	bool isCollideWithPlayer();
	bool init();
	bool isRed();
	Point getPosition();

	Sprite* bottleSprite;
private:
	Player* m_player;
	bool red;
	bool play;
	Vec2 vec;
};

#endif
