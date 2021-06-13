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
		//coin->stopAllActions();
		if (isCollideWithPlayer())
		{
			//removeChild(coin);
			//unschedule(CC_SCHEDULE_SELECTOR(Coin::update));
			log("coin position: (%f,%f)", getPosition().x, getPosition().y);
			log("m_player position:(%f,%f)", m_player->getPosition().x, m_player->getPosition().y);
			return;
		}
		if ((coin->getPosition() - m_player->getPosition()).getLength()<100)
		{
			return;
		}

		//flyAni(m_player->getPosition());
		flyAni(m_player->getPosition()-coin->getPosition());
	}
	log("m_player position:(%f,%f)", m_player->getPosition().x, m_player->getPosition().y);
	log("coin position: (%f,%f)", getPosition().x, getPosition().y);
	log("move:(%f,%f)", (m_player->getPosition() - coin->getPosition()).x, (m_player->getPosition() - coin->getPosition()).y);
}

void Coin::disperseAni()
{
	
	vec.set(random(-1.0f, 1.0f), random(-1.0f, 1.0f));
	vec.normalize();
	log("vec position:(%f,%f)",vec.x,vec.y);
	auto disperse = MoveBy::create(1,  vec * random(1, 50));
	coin->runAction(disperse);
}

void Coin::bindPlayer(Player* player)
{
	m_player = player;
}

bool Coin::allowFlying()
{
	//return true;
	Vec2 vec = getPosition() - m_player->getPosition();
	if (vec.getLength() <= 1)
	{
		return true;
	}
	return false;
}

void Coin::flyAni(Vec2 target)
{
	Vec2 vecm = Vec2((int)m_player->getPosition().x - (int)coin->getPosition().x, (int)m_player->getPosition().y - (int)coin->getPosition().y);
	//auto fly = MoveTo::create(target.getLength()/2, Vec2((int)target.x,(int)target.y));
	auto fly = MoveBy::create(target.getLength() / 2,vecm );
	
	coin->runAction(fly);
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
	//schedule(CC_SCHEDULE_SELECTOR(Coin::update));
	return true;
}

bool Coin::isGolden(bool goldenType)
{

	return goldenType;
}

void Coin::setPosition(Vec2 vec)
{
	coin->setPosition(vec);
}

Point Coin::getPosition()
{
	return coin->getPosition();
}

