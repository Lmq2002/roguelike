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
		//人箱向量
		Point pos = m_player->getPosition() - getParent()->getPosition();
		if (m_player)
		{
			if (pos.getLength() > 10)
			{
				flyAni(m_player->getPosition());
				//币箱-人箱=币人
				if ((coin->getPosition() - pos).getLength() < 5)
				{
					m_player->addCoin(golden);
					removeChild(coin);
					unschedule(CC_SCHEDULE_SELECTOR(Coin::update));
					return;
				}
			}
		}



		//if ((coin->getPosition() - pos).getLength()<20)
		//{
		//	//log("able to xiaoshi!");
		//	m_player->addCoin(1);
		//	removeChild(coin);
		//	unschedule(CC_SCHEDULE_SELECTOR(Coin::update));
		//	return;
		//}
		//if (m_player)
		//{
		//	stopAllActions();
		//	flyAni(m_player->getPosition());
		//}
	}
	
}

void Coin::disperseAni()
{
	
	vec.set(random(-1.0f, 1.0f), random(-1.0f, 1.0f));
	vec.normalize();
	//log("vec position:(%f,%f)",vec.x,vec.y);
	auto disperse = MoveBy::create(0.3f,  vec * random(1, 50));

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
	if (vec.getLength() <= 20)
	{
		return true;
	}
	return false;
}

void Coin::flyAni(Vec2 target)
{
	/*Point dstPos = this->getParent()->convertToNodeSpace(target);*/
	Point dstPos =  target-this->getParent()->getPosition();
	Point vecm =getParent()->getPosition()+ getPosition() - target;
	vecm.normalize();
	coin->setPosition(getPosition() - 5*vecm);	
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
	return golden;
	//return goldenType;
}

//void Coin::setPosition(Vec2 vec)
//{
//	coin->setPosition(vec);
//}

Point Coin::getPosition()
{
	return coin->getPosition();
}

