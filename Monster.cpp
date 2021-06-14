#include "Monster.h"

Monster::Monster()
{
	m_isAlive = true;
	right = false;
}

Monster::~Monster()
{
}

bool Monster::init()
{
	show();
	//this->scheduleUpdateWithPriority(3);
	schedule(CC_SCHEDULE_SELECTOR(Monster::update),1);
	return true;
}

void Monster::update(float dt)
{
	if (isAlive()) {
		if (isCollideWithPlayer(m_player)) {
			m_player->hitted(3);
			m_isAlive = false;
		}
		findAndAct();
	}
	if (!isAlive()) {
		hide();
	}
}

void Monster::show()
{
	if (getSprite() != NULL) {
		setVisible(true);   //设置可见
		m_isAlive = true;   //标记怪物为活动状态
	}
}



void Monster::setTiledMapPosition(Point position)
{
	if (getSprite() != NULL) {
		/*初始化怪物坐标*/
		setPosition(position);
	}
}

bool Monster::isAlive()
{
	return m_isAlive;
}

bool Monster::isCollideWithPlayer(Player* player)
{
	//获取碰撞检查对象的矩阵区域
	Rect entityRect = player->getBoundingBox();

	Point monsterPos = getPosition();

	//判断中心点是否有交集
	return entityRect.containsPoint(monsterPos);
}

void Monster::bindPlayer(Player* player)
{
	m_player = player;
}

void Monster::hide()
{
	if (getSprite() != NULL) {
		setVisible(false);   //设置可见
		m_isAlive = false;   //标记怪物为活动状态
	}
}

void Monster::findAndAct()
{
	stopAllActions();
	Point vec = m_player->getPosition() - getPosition();
	log("vec position.x: %f", vec.x);
	if (vec.getLength() < 200)
	{
		if (vec.x > 0)//guai ren
			if (!right)//朝左
			{
				log("isRight: %d", int(right));
				m_sprite->setFlippedX(true);
				right = true;
			}
		if (vec.x < 0)
			if (right)
			{
				log("isRight: %d", int(right));
				m_sprite->setFlippedX(false);
				right = false;
			}
		//vec.normalize();
		//runAction(MoveBy::create(vec.getLength()/1, vec*random(vec.getLength()*0.1f,vec.getLength()*0.3f)));
		Point vec1 = m_player->getPosition();
		//vec1.normalize();
		runAction(MoveTo::create(vec.getLength() / 100, vec1 + Vec2(random(-1.0f, 1.0f) * 10, random(-1.0f, 1.0f) * 10)));
	}

}

