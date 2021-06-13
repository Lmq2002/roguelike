#pragma once
#ifndef _COINBOX_H_
#define _COINBOX_H_
#include "cocos2d.h"
#include "Coin.h"
using namespace cocos2d;
USING_NS_CC;


class CoinBox:
	public Node
{
public:
	CoinBox();
	~CoinBox();
	CREATE_FUNC(CoinBox);
	bool init();
	void showBox();
	void openAni();

private:
	Sprite* coinBox;

};

#endif // !_COINBOX_H_