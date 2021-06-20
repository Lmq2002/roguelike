#include "Player.h"
#include "MessageBoard.h"
#define schedule_selector(_SELECTOR) static_cast<cocos2d::SEL_SCHEDULE>(&_SELECTOR)
//#include <sstream>
//#include "ui/CocosGUI.h"
extern int direction_x, direction_y;

int Player::m_iHP = 10;
int Player::m_iMp = 200;
int Player::m_defence =10;
int Player::m_speed = 2;
int Player::m_dfpower = 0;
int Player::m_attack = 5;
int Player::m_bulletGrade = 0;
int Player::m_swordGrade = 0;
int Player::m_coin = 0;


Player::Player()
{
	//��ʼ��Ѫ��
	//m_iHP = 10;
	m_isAlive = true;
	
	m_bulletType = "Gun";
}

bool Player::init()
{
	//ע��һ����Ļ�����¼�
	registeTouchEvent();
	start_time = clock();

	return true;
}

void Player::run()
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile("boys.plist", "boys.png");  //����֡����

	auto cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*>frameList;

	//�������� ,������ӵ��б���
	frameList.pushBack(cache->getSpriteFrameByName("boy_run1.png"));
	frameList.pushBack(cache->getSpriteFrameByName("boy_run2.png"));
	

	//���ϼ�¼��������������
	Animation* animation = Animation::createWithSpriteFrames(frameList);



	animation->setLoops(-1);
	//���Ŷ������˴�Ϊ��Զ����

	animation->setDelayPerUnit(0.1f);  //���ò����ٶ�


	//������������
	Animate* animate = Animate::create(animation);

	//����ִ�ж���
	m_sprite->runAction(animate);
	//addChild()


}

void Player::atk()
{
	//BulletBase* bullet = m_bulletMgr->getAnyUnUsedBullet();
	//if (bullet != NULL) {
	//	
	//}
}

void Player::update(float dt)
{	
	//setBltRect();
	nowTime = float(clock() - start_time) / 1000;
	//nowTime = nowTime / 1000;
	time = nowTime;	

	if (time % 2 == 0) {
		_time = 0;
	}
	time_2 = time % 2 + _time;

	if (m_defence == 0) {
		if (time - record_time_defence == 5) {
			m_defence++;
			record_time_defence--;
		}
		
	}


	if (time_2 == 1) {
		if (m_defence < 10&&m_defence>0) {
			m_defence++;
			_time = 1;
		}
	}
	//if (time_2 == 1) {
	//	_time = 0;
	//}


	float speed = 0.01f;
	auto action_right = Sequence::create(
		//ScaleTo::create(speed, -1.f, 1.f),  //ˮƽ��ת
		ScaleTo::create(speed, 1.f, 1.f),   //ˮƽ��ԭ
		nullptr);

	auto action_left = Sequence::create(
		ScaleTo::create(speed, -1.f, 1.f),  //ˮƽ��ת
		//ScaleTo::create(speed, 1.f, 1.f),   //ˮƽ��ԭ
		nullptr);

	extern int direction_x, direction_y;
	//log("%d", direction_x);
	if (direction_x == 1|| direction_x == 10)
	{
		m_sprite->runAction(action_right);

		if (direction_y == 0 || direction_y == 1)
			run();   //�ý�ɫ��
		if (direction_x == 1)
			direction_x = 2;
		if (direction_y == 1)
			direction_y = 2;
		
	}
	if (direction_x == -1|| direction_x == -10)
	{
		m_sprite->runAction(action_left);

		if (direction_y == 0 || direction_y == 1)
			run();
		if (direction_x == -1)
			direction_x = -2;
		if (direction_y == 1)
			direction_y = 2;

		
	}
	

	//if (!isAlive()) {
	//	m_sprite->setVisible(false);
	//}
}

void Player::setViewPointByPlayer()
{
	if (m_sprite == NULL) {
		return;
	}
	Layer* parent = (Layer*)getParent();


	//��ͼ��������
	Size mapTiledNum = m_map->getMapSize();
	//log("get the mapTiledNum");

	//��ͼ�������Ӵ�С
	Size tiledSize = m_map->getTileSize();
	//log("get the tiledSize");

	//��ͼ��С
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	//��Ļ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//��������
	Point spritePos = getPosition();
	//log("%f", spritePos.x);

	//�����������С����Ļ��һ�룬��ȡ��Ļ�е�����
	//����ȡ��������
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	//float x = spritePos.x;
	//float y = spritePos.y;

	//���x,y����������Ͻǵļ���ֵ����ȡ����ֵ����
	//����ֵָ���ǲ��õ�ͼ������Ļ��ɳ��ֺڱߵļ�������
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	//Ŀ���
	Point destPos = Point(x, y);

	//��Ļ�е�
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);
	//Point centerPos = Vec2(Director::getInstance()->getVisibleSize() / 2);
	//������Ļ�е�����ƶ���Ŀ�ĵ�֮��ľ���
	Point viewPos = centerPos - destPos;
	//log("viewPos");

	parent->setPosition(viewPos);

}

void Player::setTagPosition(int x, int y)
{
	/****************�ж�ǰ���Ƿ񲻿�ͨ��*****************/
	//ȡ����ǰ��������

	Size spriteSize = m_sprite->getContentSize();
	log("x,y��%d,%d", x, y);

	Point dstPos = Point(x + spriteSize.width / 2, y);
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
				return;
			}

		}
		if (propertiesMap.find("food") != propertiesMap.end()) {
			Value prop = propertiesMap.at("food");
			//�ж�Collidableֵ�Ƿ�Ϊtrue,����ǣ������ƶ�
			if (prop.asString().compare("true") == 0) {
				return;
			}
		}
		if (propertiesMap.find("win") != propertiesMap.end()) {
			//ȡ�ø��ӵ�win����ֵ���ж��Ƿ�Ϊtrue������ǣ����л�����
			Value prop = properties.asValueMap().at("win");
			if (prop.asString().compare("true") == 0) {

				auto listener = EventListenerKeyboard::create();

				listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
					if (keyCode == EventKeyboard::KeyCode::KEY_J) {
						//setiXSpeed(2);
						//Director::sharedDirector()->replaceScene(TransitionFade::create(1.5f, scene));
						//getPlayerInstance();
						//_playerInstance = this;
						//Director::getInstance()->pause();
						CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
						Director::getInstance()->replaceScene(Scene_battleMap_1::createScene());
						//Director::getInstance()->resume();
						//this->onEnter();
					}


				};
				listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
					if (keyCode == EventKeyboard::KeyCode::KEY_J) {
						//setiXSpeed(0);
						//Director::getInstance()->replaceScene(Scene_battleMap_2::createScene());
					}
				};
				_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
			}
		}
		if (propertiesMap.find("info") != propertiesMap.end())
		{
			Value prop = properties.asValueMap().at("info");
			if (prop.asString().compare("true") == 0) {

				auto listener = EventListenerKeyboard::create();

				listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
					if (keyCode == EventKeyboard::KeyCode::KEY_J) {
						//setiXSpeed(2);
						Director::getInstance()->pushScene(MessageBoard::createScene());
					}


				};
				//listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
				//	if (keyCode == EventKeyboard::KeyCode::KEY_J) {
				//		//setiXSpeed(0);
				//		Director::getInstance()->pushScene(MessageBoard::createScene());
				//	}
				//};
				_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
			}
		}


		//if (propertiesMap.find("box") != propertiesMap.end()) {
		//	//ȡ�ø��ӵ�win����ֵ���ж��Ƿ�Ϊtrue������ǣ����л�����
		//	Value prop = properties.asValueMap().at("box");
		//	if (prop.asString().compare("true") == 0) {

		//		auto listener = EventListenerKeyboard::create();

		//		listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		//			if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		//				//int n = random(0, 5);
		//				//switch (n){
		//				//	case 0:

		//				//}
		//				//setiXSpeed(2);
		//				//Director::getInstance()->replaceScene(HelloWorld::createScene());						
		//				setBulletType("redGun");
		//				
		//			}


		//		};
		//		listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		//			if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		//				//setiXSpeed(0);
		//				//Director::getInstance()->replaceScene(HelloWorld::createScene());
		//				setBulletType("redGun");
		//				
		//			}
		//		};
		//		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		//	}
		//}
	}


	Characters::setTagPosition(x, y);

	//������Ϊ�����ƶ���ͼ
	setViewPointByPlayer();

}

//void Player::setTiledMap(TMXTiledMap* map)
//{
//	this->m_map = map;
//
//	//����metaͼ�������
//	this->meta = m_map->getLayer("meta");
//	this->meta->setVisible(false);    //��Ҫ��ʾ
//}

Point Player::pCollision(int x,int y)
{
	

	//��ȡ�������ӵĴ�С
	auto m_segment_width = m_map->getTileSize().width;
	auto m_segment_height = m_map->getTileSize().height;


	Size spriteSize = m_sprite->getContentSize();

	float X = x + spriteSize.width / 2, Y = y;

	//if (direction_x == 1 || direction_x == 2)
	//{
	//	X = x + spriteSize.width / 2 + m_segment_width / 4;
	//	//Y = y;
	//}
	//else if (direction_x == -1 || direction_x == -2)
	//{
	//	X = x + spriteSize.width / 4;
	//	//Y = y;
	//}
	//else
	//{
	//	X = x;
	//}
	//if (direction_y == -1)
	//{
	//	//X = x + spriteSize.width / 2 + m_segment_width / 4;
	//	Y = y - m_segment_height / 2 + spriteSize.height / 4;
	//}
	//else 
	//{
	//	//X = x + spriteSize.width / 4;
	//	Y = y;
	//}
	
	return Point(X, Y);
}

void Player::addWeapon()
{
	//Sprite* m_gun = Sprite::create("Gun/Gun0.png");
	Sprite* m_gun = Sprite::create("redGun.png");
	
	m_weapon = Weapons::create();

	m_weapon->bindSprite(m_gun);
	
	//m_weapon->setAnchorPoint(Vec2(-1,-1));
	//m_weapon->setPosition(getPosition());
	m_weapon->setPosition(Point(getPosition().x , getPosition().y - 10));
  
	this->addChild(m_weapon, 4);

}

void Player::addKnife()
{
	Sprite* m_knife = Sprite::create("BigKnife.png");

	m_knife->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	m_knife->setPosition(Point(getPosition().x, getPosition().y - 10));

	this->addChild(m_knife, -1);
}

void Player::setBulletType(string bulletType)
{
	m_bulletType = bulletType;
}



void Player::loadBullet()
{
	//���ȴ���һ���ӵ����󣨾��飩
	if (getBulletType() == "Gun") {
		m_bullet = BulletGun::create();
	}
	if (getBulletType() == "redGun") {
		m_bullet = BulletRedGun::create();
	}
	
	//m_bullet->setPosition(m_weapon->getPosition());
	//m_bullet->setPosition(getPosition());
	m_bullet->setPosition(Point(getPosition().x, getPosition().y ));

	m_iMp -= m_bullet->getMagicCost();

	m_bullet->setUsed(false);
	m_bullet->bindPlayer(this);

	m_bullet->bindMonsterList(mMonsterList);  //��MonsterList�����ӵ�

	m_bullet->setTiledMap(m_map);//�����ͼ
	m_map->addChild(m_bullet);


	/*m_bullet->schedule(schedule_selector(),
		);*/
}

void Player::bulletLogicCheck(float dt)
{
	if (m_bullet->isCollision()) {
		//����
		log("attack!!!");

		m_bullet->setUsed(false);
	}
}

void Player::fire()
{
	m_bullet->getDirection(m_degree);
	m_bullet->setUsed(true);

	//m_bullet->onLockAim(m_aim);
}

float Player::getDirection()
{
	return m_degree;
}

void Player::setDirection()
{
	//��player�У�m_aim����ʼ��ַ�Ѿ�����,���贫��
	Point dstPos = this->getParent()->convertToNodeSpace(m_aim);

	//�����������
	Point shootVector = getPosition() - dstPos;

	//������׼��(����������Ϊ1)
	shootVector.normalize();
	//�����ת�Ļ���
	float weapon_radians = atan2(shootVector.y, -shootVector.x);
	float radians = atan2(shootVector.y, shootVector.x);
	//������ת���ɽǶ�
	float weapon_degree = CC_RADIANS_TO_DEGREES(weapon_radians);
	float degree = CC_RADIANS_TO_DEGREES(radians);
	m_degree = degree + 180;
	auto action_updown = Sequence::create(
		ScaleTo::create(0.0f, 1.f, -1.f),   //���·�ת
		nullptr);
	auto action_back = Sequence::create(
		ScaleTo::create(0.0f, 1.f, 1.f),   //��ԭ
		nullptr);

	if (weapon_degree > -90 && weapon_degree < 90) {
		m_weapon->runAction(action_back);
	}
	else {
		m_weapon->runAction(action_updown);
	}

	//if (dstPos.x < getPosition().x) {
	//	auto action_left = Sequence::create(
	//		ScaleTo::create(0.0f, -1.f, 1.f),  //ˮƽ��ת
	//		//ScaleTo::create(speed, 1.f, 1.f),   //ˮƽ��ԭ
	//		nullptr);
	//	degree += 2 * degree-180;
	//	//degree = 0-degree;

	//	m_weapon->runAction(action_left);
	//}
	//else {
	//	//float speed = 0.01f;
	//	auto action_right = Sequence::create(
	//		//ScaleTo::create(speed, -1.f, 1.f),  //ˮƽ��ת
	//		ScaleTo::create(0.0f, 1.f, 1.f),   //ˮƽ��ԭ
	//		nullptr);
	//	m_weapon->runAction(action_right);
	//}

	//������ת��Ҫ��������һ���ٶȣ����������ת�ٶ�Ϊ 2�� (rad/s)
	//float rotateSpeed = 20 * M_PI;
	//��ô��ת1��������ʱ��Ϊ
	//float rotate_1rad_time = 1 / rotateSpeed;
	//������ת��ʱ��Ϊ
	//float rotateDuration = fabs(radians * rotate_1rad_time);

	m_weapon->setRotation(weapon_degree);
	//FiniteTimeAction* actionRotateTo = RotateTo::create(0.0, degree);//��ת����
	//m_bullet->runAction(actionRotateTo);
	//m_bullet->setRotation(degree);
	//���ִ����ת
	//m_weapon->runAction(RotateTo::create(rotateDuration, degree));
}

//Rect Player::getBltRect()
//{
//	return m_bullet->getBltRect();
//}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
void Player::hitted(int attack)
{
	int damage;
	damage = attack - m_dfpower;
	if (damage <= 0) {
		damage = 0;
	}
	
	if (getSprite() == NULL)
	{
		return;
	}

	//char hurt = damage + 48;
	string BckBlood = "-";
	BckBlood += to_string(damage);
	
	/*��ѪƮ����Ч*/
	auto flyWord = Label::createWithTTF(BckBlood, "fonts/Marker Felt.ttf", 12);  //��ӡһ����ǩ
	if (flyWord == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// ����������λ�ô���
		flyWord->setPosition(m_sprite->getPosition());

		// add the label as a child to this layer
		this->addChild(flyWord, 1);
	}

	//Label* flyWord = Label::createWithTTF("BckBlood", "fonts / Marker Felt.ttf", 32);
	//auto item_flyWord = MenuItemLabel::create(flyWord, NULL);


	//item_flyWord->setPosition(m_sprite->getPosition());
	flyWord->setColor(Color3B(255, 0, 0));
	auto flying = MoveBy::create(0.8f, Point(0, 35));//0.8������70����
	flyWord->runAction(flying);
	auto fadeOut = FadeOut::create(0.8f);
	flyWord->runAction(fadeOut);


	//this->addChild(item_flyWord, 5);

	//flyWord->setVisible(false);


	//FlyWord* flyWord = FlyWord::create(BckBlood,32,m_sprite->getPosition());
	//this->addChild(flyWord);
	//flowWord->showWord(, getSprite()->getPosition());

	if (m_defence > 0) {
		m_defence -= damage;
		if (m_defence <= 0) {
			m_defence = 0;
			record_time_defence = nowTime;
		}
	}
	else {
		m_iHP -= damage;
	}

	if (m_iHP <= 0) {
		m_iHP = 0;
		m_isAlive = false;
	}

	//�������ֶ���
	auto backMove = MoveBy::create(0.1f, Point(-20, 0));
	auto forwardMove = MoveBy::create(0.1f, Point(20, 0));
	auto backRotate = RotateBy::create(0.1f, -5, 0);
	auto forwardRotate = RotateBy::create(0.1f, 5, 0);

	//��ϳ����ֶ���
	auto backActions = Spawn::create(backMove, backRotate, NULL);
	auto forwardActions = Spawn::create(forwardMove, forwardRotate, NULL);

	auto actions = Sequence::create(backActions, forwardActions, NULL);

	stopAllActions();  //��ֹ֮ͣǰ����
	resetData();       //��������
	runAction(actions);//ִ�ж���
}

int Player::getiHP()
{
	return this->m_iHP;
}

int Player::getiMP()
{
	return m_iMp;
}

int Player::getDefence()
{
	return this->m_defence;
}

int Player::getSpeed()
{
	return this->m_speed;
}

bool Player::isAlive()
{
	return m_isAlive;
}

int Player::getAttack()
{
	return m_attack;
}

void Player::registeTouchEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		if (m_iMp >= 0) {
			loadBullet();

			//m_weapon->setDirection(m_aim);
			if (m_iMp - m_bullet->getMagicCost() >= 0) {
				m_aim = touch->getLocation();
				setDirection();

				log("%f,%f", getPosition().x, getPosition().y);
				log("%f,%f", m_aim.x, m_aim.y);
				fire();
			}
		}
		return true; // if you are consuming it
	};

	// trigger when moving touch
	listener->onTouchMoved = [this](Touch* touch, Event* event) {
		// your code
		//m_weapon->setDirection(m_aim);
		setDirection();
	};

	// trigger when you let up
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		// your code
		//m_weapon->setDirection(m_aim);
		setDirection();
		//fire();
	};

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Player::resetData()
{
	setScale(1.0f);
	setRotation(0);
}



string Player::getBulletType()
{
	return m_bulletType;
}

void Player::bkBlue(int blue)
{
	m_iMp += blue;

	if (m_iMp >= 200) {
		m_iMp = 200;
	}
}

void Player::bkBlood(int blood)
{
	m_iHP += blood;

	if (m_iHP >= 10) {
		m_iHP = 10;
	}
}

void Player::addCoin(int addNum)
{
	m_coin += addNum;
}

int Player::getCoin()
{
	return m_coin;
}

void Player::addBottle(bool redType)
{
	if (redType)
	{
		log(" HP shoule add hp!");
		m_iHP += 3;
		if (m_iHP > 10) {
			m_iHP = 10;
		}
	}
	else
	{
		log("MP should add up!");
		m_iMp += 80;
		if (m_iMp > 200) {
			m_iMp = 200;
		}
	}
}

void Player::getMonsterList(Vector<Monster*> m_monsterList)
{
	mMonsterList = m_monsterList;
}

//void Player::getDistanceWithMonster()
//{
//	float distance = pow(m_player->getPosition().x - getPosition().x, 2) +
//		pow(m_player->getPosition().y - getPosition().y, 2);
//	distance_with_player = sqrt(distance);
//}

//Player* Player::getPlayer()
//{
//	return this;
//}





//void Player::getAim(Point aim)
//{
//	m_aim = aim;
//}

//BulletBase* Player::getPBullet()
//{
//	return m_bullet;
//}

//void Player::setBltRect()
//{
//	bltRect = m_bullet->getBltRect();
//}

//void Player::special_ground()
//{
//
//}

//Point Player::tileCoordForPosition(Point pos)
//{
//	
//	//log("%d", tiledSize.width);
//	int x = pos.x / m_map->getContentSize().width * m_map->getMapSize().width;
//	int y = m_map->getMapSize().height - pos.y /m_map->getContentSize().height * m_map->getMapSize().height;
//	
//	//cocos2d-x��Ĭ��Y�������������ϵģ�����Ҫ��һ���������
//	//log("getMapSize:%f, %f", mapTiledNum.width, mapTiledNum.height);
//	//log("getTileSize:%f, %f", tiledSize.width, tiledSize.height);
//	//����������㿪ʼ����
//	if (x > 0) {
//		x -= 1;
//	}
//	if (y > 0) {
//		y -= 0;
//	}
//
//	//log("%d,%d", x, y);
//	return Point(x, y);
//}
