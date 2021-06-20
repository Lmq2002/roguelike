#include "Monster.h"

//Monster::Monster()
//{
//	m_isAlive = false;
//	m_hp = 10;
//	m_attack = 3;
//	m_attackNum = 3;
//	bkBlue = 3;
//}
//
//Monster::~Monster()
//{
//}

//bool Monster::init()
//{
//	move_x = 0;
//	move_y = 0;
//
//	start_time = clock();
//	show();
//	this->scheduleUpdate();
//	return true;
//}

void Monster::update(float dt)
{
	shot_direction = 0;
	Point mstCurPos = getTagPosition();
	getDistanceWithPlayer();  //��ȡ���ɫ֮��ľ��룬�ж��Ƿ�Ҫ����
	//log("%f", distance_with_player);
	nowTime = float(clock() - start_time);
	nowTime = nowTime / 1000;
	int _time = nowTime;
	int time = nowTime;
	time = time % 3;

	if (type == 1) {
		if (collisionWithPlayer() && isAttacked == false) {
			m_player->hitted(m_attack);
			isAttacked = true;
			time_5 = nowTime;
		}
	}
	if (time - time_5 == 2) {
		isAttacked == false;
	}

	//log("%d",time);
	if (time == 0) {
		stopAllActions();
		move_x = random(-2.0f, 2.0f);
		move_y = random(-2.0f, 2.0f);
		if (type == 1) {
			move_x = move_x * 2;
			move_y = move_y * 2;
		}
	}

	//log("%d,%d", move_x, move_y);
	if (time == 1 || time == 2) {
		setTagPosition(mstCurPos.x + move_x, mstCurPos.y + move_y);
	}

	if (isAlive()) {
		//if (isCollideWithBullet()) {
		//	m_player->hitted(m_attack);
		//	m_hp -= m_player->getAttack();
		//	//m_isAlive = false;

		if (m_hp <= 0)
		{
			m_hp = 0;
			m_isAlive = false;
		}
		//m_isAlive = false;
	}

	if (!isAlive()) {
		hide();
	}

	//���������ÿ3�����һ�ι���
	if (record_time_mstAttack == 0) {
		if (distance_with_player < 150) {
			record_time_mstAttack = _time;
		}
	}
	if (_time > 4) {
		if (_time - record_time_mstAttack == 3) {
			for (int n = 0; n < m_attackNum; n++) {
				shot_direction = (n - 1) * 45;
				//m_degree += 45.0f;
				//log("%f", m_degree);
				Attack();

			}
			record_time_mstAttack = 0;
		}
	}
}

void Monster::show()
{
	if (getSprite() != NULL) {
		setVisible(true);   //���ÿɼ�
		m_isAlive = true;   //��ǹ���Ϊ�״̬
	}
}

void Monster::setTiledMapPosition(Point position)
{
	if (getSprite() != NULL) {
		/*��ʼ����������*/
		setPosition(position);
	}
}

bool Monster::isAlive()
{
	return m_isAlive;
}


//bool Monster::ifHittedByBullet()
//{
//	Rect mstRect = getBoundingBox();
//	if (mstRect.containsPoint(pBullet->getPosition())) {
//		return true;
//	}
//
//	return false;
//}

void Monster::bindPlayer(Player* player)
{
	m_player = player;
}

void Monster::hide()
{
	if (getSprite() != NULL) {
		setVisible(false);   //���ÿɼ�
		m_player->bkBlue(bkBlue);
		m_isAlive = false;   //��ǹ���Ϊ�״̬
		m_map->removeChild(this);
	}
}

void Monster::setTagPosition(int x, int y)
{
	/****************�ж�ǰ���Ƿ񲻿�ͨ��*****************/
	Size spriteSize = m_sprite->getContentSize();
	//log("x,y��%d,%d", x, y);

	Point dstPos = Point(x + spriteSize.width / 4, y - spriteSize.height / 2);
	//Point dstPos = Point(x, y);
	//log("pos:%f, %f", spriteSize.width, spriteSize.height);
	//��õ�ǰ����ǰ�������ڵ�ͼ�еĸ���λ��
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	//log("character position: %f,%f", tiledPos.x, tiledPos.y);

	//��ȡ��ͼ���ӵ�Ψһ��ʶ
	int tiledGid = meta->getTileGIDAt(tiledPos);
	//log("%d", tiledGid);

	//��Ϊ0����������������
	if (tiledGid != 0) {
		/*
		��ȡ�õ�ͼ���ӵ��������ԣ�Ŀǰ����ֻ��һ��Collidable����
		����������meta��ģ���ͬʱҲ������������ͼ�ģ����Ի�ȡ���ӵ���������
		ʱ��ͨ������Ψһ��ʶ�ڵ�ͼ�л��
		*/
		Value properties = m_map->getPropertiesForGID(tiledGid);

		ValueMap propertiesMap = properties.asValueMap();
		//ȡ�ø��ӵ�colliable����ֵ

		if (propertiesMap.find("Collidable") != propertiesMap.end()) {
			//ȡ�ø��ӵ�Collidable����ֵ
			Value prop = propertiesMap.at("Collidable");
			//�ж�Collidableֵ�Ƿ�Ϊtrue,����ǣ������ƶ�
			if (prop.asString().compare("true") == 0) {
				//stopAllActions();
				return;
			}

		}
		if (propertiesMap.find("fence_wooden") != propertiesMap.end()) {
			//ȡ�ø��ӵ�Collidable����ֵ
			Value prop = propertiesMap.at("fence_wooden");
			//�ж�Collidableֵ�Ƿ�Ϊtrue,����ǣ������ƶ�
			if (prop.asString().compare("true") == 0) {
				//stopAllActions();
				return;
			}

		}
		if (propertiesMap.find("food") != propertiesMap.end()) {
			Value prop = propertiesMap.at("food");
			//�ж�Collidableֵ�Ƿ�Ϊtrue,����ǣ������ƶ�
			if (prop.asString().compare("true") == 0) {
				//stopAllActions();
				return;
			}
		}
	}


	Characters::setTagPosition(x, y);

}

void Monster::getHitted(int attack)
{

	m_hp -= attack;

	string BckBlood = "-";
	BckBlood += to_string(attack);

	auto flyWord = Label::createWithTTF(BckBlood, "fonts/Marker Felt.ttf", 12);  //��ӡһ����ǩ

	flyWord->setPosition(m_sprite->getPosition());

	// add the label as a child to this layer
	this->addChild(flyWord, 1);

	flyWord->setColor(Color3B(255, 0, 0));
	auto flying = MoveBy::create(0.8f, Point(0, 35));//0.8������70����
	flyWord->runAction(flying);
	auto fadeOut = FadeOut::create(0.8f);
	flyWord->runAction(fadeOut);

	//removeChild(flyWord);

}

//void Monster::Attack()
//{
//	//���ȴ���һ���ӵ����󣨾��飩
//	m_bullet = BulletMstGun::create();
//
//	m_bullet->setPosition(getPosition());
//
//	//m_iMp -= m_bullet->getMagicCost();
//
//	m_bullet->setUsed(false);
//	m_bullet->bindPlayer(m_player);
//
//	m_bullet->setTiledMap(m_map);//�����ͼ
//	m_map->addChild(m_bullet);
//
//	setDegree();
//	log("%f", m_degree);
//	m_bullet->getDirection(m_degree + shot_direction);
//	m_bullet->setUsed(true);
//
//}

void Monster::setDegree()
{
	Point shootVector = getPosition() - m_player->getPosition();

	shootVector.normalize();

	float radians = atan2(shootVector.y, shootVector.x);
	float degree = CC_RADIANS_TO_DEGREES(radians);

	m_degree = degree + 180;
}

void Monster::getDistanceWithPlayer()
{
	float distance = pow(m_player->getPosition().x - getPosition().x, 2) +
		             pow(m_player->getPosition().y - getPosition().y, 2);
	distance_with_player = sqrt(distance);
}

bool Monster::collisionWithPlayer()
{
	//��ȡ��ײ������ľ�������
	Rect entityRect = m_player->getBoundingBox();
	//Rect entityRect = this->getBoundingBox();

	Point monsterPos = getPosition();
	//Point bulletPos=m_player.m

	//�ж����ĵ��Ƿ��н���
	return entityRect.containsPoint(monsterPos);

}




//void Monster::bindBullet(BulletBase* bullet)
//{
//	pBullet = bullet;
//}



//************************************************************************************
MonsterStriker::MonsterStriker()
{
	m_isAlive = false;
	m_hp = 10;
	m_attack = 3;
	m_attackNum = 3;
	bkBlue = 3;
	type = 0;
}

MonsterStriker::~MonsterStriker()
{
}

bool MonsterStriker::init()
{
	move_x = 0;
	move_y = 0;

	start_time = clock();
	show();
	this->scheduleUpdate();
	return true;
}

void MonsterStriker::Attack()
{
	//���ȴ���һ���ӵ����󣨾��飩
	m_bullet = BulletMstGun::create();

	m_bullet->setPosition(getPosition());

	//m_iMp -= m_bullet->getMagicCost();

	m_bullet->setUsed(false);
	m_bullet->bindPlayer(m_player);

	m_bullet->setTiledMap(m_map);//�����ͼ
	m_map->addChild(m_bullet);

	setDegree();
	log("%f", m_degree);
	m_bullet->getDirection(m_degree + shot_direction);
	m_bullet->setUsed(true);
}



//**************************************************************************************

MonsterPig::MonsterPig()
{
	m_isAlive = false;
	m_hp = 20;
	m_attack = 6;
	m_attackNum = 1;
	bkBlue = 6;
	type = 1;
	isAttacked = false;
}

MonsterPig::~MonsterPig()
{
}

bool MonsterPig::init()
{
	move_x = 0;
	move_y = 0;

	start_time = clock();
	show();
	this->scheduleUpdate();
	return true;
}

void MonsterPig::Attack()
{

}


