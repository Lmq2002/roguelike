#include "CoinBox.h"

CoinBox::CoinBox()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("coinBox.plist");
	coinBox = Sprite::createWithSpriteFrameName("coinBoxClose.png");
}

CoinBox::~CoinBox()
{
}

bool CoinBox::init()
{

	return true;
}

void CoinBox::showBox()
{
	addChild(coinBox);
}

void CoinBox::openAni()
{
	auto cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*>frameList;
	frameList.pushBack(cache->getSpriteFrameByName("coinBoxOpen.png"));
	frameList.pushBack(cache->getSpriteFrameByName("coinBoxClose.png"));
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);  
	Animate* animate = Animate::create(animation);
	coinBox->runAction(animate);

	Vector<Coin*> coinList;
	coinList.pushBack(Coin::createCoin(true));
	coinList.pushBack(Coin::createCoin(true));
	int oper = coinList.empty() ? -1 : coinList.size() - 1;
	for (int i = 0; i <= oper && i >= 0; i++)
	{
		addChild(coinList.at(i));
		coinList.at(i)->disperseAni();
	}
}
