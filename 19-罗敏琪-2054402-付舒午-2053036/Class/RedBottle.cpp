#include "RedBottle.h"

RedBottle* RedBottle::createRedBottle(bool redType)
{
	RedBottle* redBottle = new RedBottle;
	redBottle->red = redType;
	if (redBottle && redBottle->init())
	{
		redBottle->autorelease();
		return redBottle;
	}
	else
	{
		delete redBottle;
		redBottle = NULL;
	}

	return NULL;
}

void RedBottle::update(float dt)
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
		if (m_player)
		{
			//stopAllActions();
			if (pos.getLength() > 20)
			{
				flyAni(m_player->getPosition());
				if ((bottleSprite->getPosition() - pos).getLength() < 5)
				{
					m_player->addBottle(red);
					removeChild(bottleSprite);
					unschedule(CC_SCHEDULE_SELECTOR(RedBottle::update));
					return;
					/*	}*/
				}
			}
		}

	}
}

void RedBottle::disperseAni()
{
	vec.set(random(-1.0f, 1.0f), random(-1.0f, 1.0f));
	vec.normalize();
	auto disperse = MoveBy::create(0.5f, vec * random(1, 70));
	bottleSprite->runAction(disperse);
	/*m_action = MoveBy::create(1.0f, vec * random(1, 70));
	bottleSprite->runAction(m_action);*/
}

void RedBottle::bindPlayer(Player* player)
{
	m_player = player;
}

bool RedBottle::allowFlying()
{
	Vec2 pos = m_player->getPosition() - getParent()->getPosition();
	Vec2 vec = getPosition() - pos;
	if (vec.getLength() <= 20)
	{
		return true;
	}
	return false;
}

void RedBottle::flyAni(Vec2 target)
{
	stopAllActions();
	Point dstPos = target - this->getParent()->getPosition();
	Point vecm = getParent()->getPosition() + getPosition() - target;
	vecm.normalize();
	bottleSprite->setPosition(getPosition()-5*vecm);
	/*auto fly = MoveTo::create(vecm.getLength() /20, dstPos);
	bottleSprite->runAction(fly);*/
}

bool RedBottle::isCollideWithPlayer()
{
	Rect entityRect = m_player->getBoundingBox();
	Point bottlePos = getPosition();

	return entityRect.containsPoint(bottlePos);
}

bool RedBottle::init()
{
	bottleSprite = Sprite::create("redBottle.png");
	addChild(bottleSprite);
	play = false;
	
	//bottleSprite->setScale(0.5f);
	if (!isRed())
	{
		bottleSprite->setColor(Color3B::BLUE);
	}
	schedule(CC_SCHEDULE_SELECTOR(RedBottle::update));
	return true;
}

bool RedBottle::isRed()
{
	return red;
}

Point RedBottle::getPosition()
{
	return bottleSprite->getPosition();
}
