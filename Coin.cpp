#include "Coin.h"
Coin::Coin()
{
	coin = Sprite::create("coin.png");
	play=false;
}

Coin::~Coin()
{
}

Coin* Coin::createCoin(bool goldenType)
{
	Coin* coin = new Coin;
	coin->golden = goldenType;
	if (coin && coin->init())
	{
		coin->autorelease();
		return coin;
	}
	else
	{
		delete coin;
		coin = NULL;
	}
	return NULL;
}

void Coin::update(float dt)
{
	if (!play)
	{
		if (allowFlying())
		{
			play = true;
		}
	}
	else
	{
		Point pos = m_player->getPosition() - getParent()->getPosition();
		if ((coin->getPosition() - pos).getLength()<20)
		{
			//log("able to xiaoshi!");
			removeChild(coin);
			unschedule(CC_SCHEDULE_SELECTOR(Coin::update));
			return;
		}
		if (m_player)
		{
			stopAllActions();
			flyAni(m_player->getPosition());
		}
	}
	
}

void Coin::disperseAni()
{
	
	vec.set(random(-1.0f, 1.0f), random(-1.0f, 1.0f));
	vec.normalize();
	log("vec position:(%f,%f)",vec.x,vec.y);
	auto disperse = MoveBy::create(1.0f,  vec * random(1, 50));

	coin->runAction(disperse);
}

void Coin::bindPlayer(Player* player)
{
	m_player = player;
}

bool Coin::allowFlying()
{
	Vec2 pos = m_player->getPosition() - getParent()->getPosition();
	Vec2 vec = getPosition() - pos;
	if (vec.getLength() <= 50)
	{
		return true;
	}
	return false;
}

void Coin::flyAni(Vec2 target)
{
	stopAllActions();
	/*Point dstPos = this->getParent()->convertToNodeSpace(target);*/
	Point dstPos =  target-this->getParent()->getPosition();
	Point vecm =getParent()->getPosition()+ getPosition() - target;
	auto fly = MoveTo::create(vecm.getLength()/50, dstPos);
	coin->runAction(fly);
	//stopAllActions();
	log("dstPos position: (%f,%f,)", dstPos.x, dstPos.y);
	log("m_player position:(%f,%f)", m_player->getPosition().x, m_player->getPosition().y);
	log("target position:(%f,%f)", target.x, target.y);
	log("coin position: (%f,%f)", getPosition().x, getPosition().y);
	log("coinBox position:(%f,%f)", getParent()->getPosition().x, getParent()->getPosition().y);
	
}

bool Coin::isCollideWithPlayer()
{
	//获取碰撞检查对象的矩阵区域
	Rect entityRect = m_player->getBoundingBox();

	Point coinPos = getPosition();
	
	//判断中心点是否有交集
	return entityRect.containsPoint(coinPos);
}

bool Coin::init()
{
	//coin = Sprite::create("coin.png");
	addChild(coin);
	coin->setScale(0.5f);
	
	if (!isGolden(golden))
	{
		coin->setColor(Color3B::BLUE);
	}
	schedule(CC_SCHEDULE_SELECTOR(Coin::update));
	return true;
}

bool Coin::isGolden(bool goldenType)
{

	return goldenType;
}

//void Coin::setPosition(Vec2 vec)
//{
//	coin->setPosition(vec);
//}

Point Coin::getPosition()
{
	return coin->getPosition();
}

