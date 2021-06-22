#pragma once
#ifndef _COIN_H_
#define _COIN_H_
#include "cocos2d.h"
#include "Player.h"
using namespace cocos2d;



class Coin:
	public Node
{
public:
	Coin();
	~Coin();
	static Coin* createCoin(bool goldenType);
	void update(float dt);
	void disperseAni();
	void bindPlayer(Player* player);
	bool allowFlying();
	void flyAni(Vec2 target);
	bool isCollideWithPlayer();
	bool init();
	bool isGolden(bool goldenType);
	//void setPosition(Vec2 vec);
	Point getPosition();
	CREATE_FUNC(Coin);
	
	Sprite* coin;

private:
	Player* m_player;
	bool golden;
	bool play;
	Vec2 vec;
};

#endif // !_COIN_H_