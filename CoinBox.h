#pragma once
#ifndef _COINBOX_H_
#define _COINBOX_H_
#include "cocos2d.h"
#include "Coin.h"
#include "RedBottle.h"
#include "Player.h"
using namespace cocos2d;
USING_NS_CC;


class CoinBox:
	 public Characters
{
public:
	CoinBox();
	~CoinBox();
	CREATE_FUNC(CoinBox);
	bool init();
	void showBox();
	void openAni();
	void bindPlayer(Player* player);
	void update(float dt);

private:
	Sprite* coinBox;
	Player* m_player;
	bool play;

};

#endif // !_COINBOX_H_