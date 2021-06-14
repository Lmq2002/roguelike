#include "CoinBox.h"

CoinBox::CoinBox()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("coinBox.plist");
	coinBox = Sprite::createWithSpriteFrameName("coinBoxClose.png");
	play = false;
}

CoinBox::~CoinBox()
{
}

bool CoinBox::init()
{
	schedule(CC_SCHEDULE_SELECTOR(CoinBox::update));
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
	frameList.pushBack(cache->getSpriteFrameByName("coinBoxClose.png"));
	frameList.pushBack(cache->getSpriteFrameByName("coinBoxOpen.png"));
	
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
		coinList.at(i)->bindPlayer(m_player);
		coinList.at(i)->setPosition(coinBox->getPosition());
		coinList.at(i)->disperseAni();
		//coinList.at(i)->flyAni(m_player->getPosition());

	}
}

void CoinBox::bindPlayer(Player* player)
{
	m_player = player;
}

void CoinBox::update(float dt)
{
	if (!play&&m_player)
	{
		log("CoinBox unOpen!");
		Vec2 pos = m_player->getPosition() - getPosition();
		if(pos.getLength()<20)
		{
			play = true;
		}
	}
	else 
	{
		openAni();
		unschedule(CC_SCHEDULE_SELECTOR(CoinBox::update));
	}
}


