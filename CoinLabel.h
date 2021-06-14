#pragma once
#ifndef _COINLABEL_H_
#define _COINLABEL_H_
#include "cocos2d.h"
#include "Player.h"
using namespace cocos2d;
USING_NS_CC;

class CoinLabel :
	public Node
{
public:
	CoinLabel();
	~CoinLabel();
	CREATE_FUNC(CoinLabel);
	/*static CoinLabel* createCoinLabel(Player* player);*/
	bool init();
	void update(float dt);
	void bindPlayer(Player* player);
	
private:
	Label* coinLabel;
	Sprite* coin;
	Player* m_player;

};

#endif // !_COIBLABEL_H_