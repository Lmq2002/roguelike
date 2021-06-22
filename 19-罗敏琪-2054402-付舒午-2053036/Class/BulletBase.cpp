#include "BulletBase.h"

BulletBase::BulletBase()
{
	m_isUsed = false;
	//m_aim = NULL;

}

BulletBase::~BulletBase()
{

}

void BulletBase::update(float dt)
{
	Move();

	Point bltCurPos = getTagPosition();

	if (type == "player" || type == "player_knife") {
		checkCollisionWithMonster();
		if (type == "player_knife") {
			nowTime = float(clock() - start_time);
			nowTime = nowTime / 1000;

			int time = nowTime;
			time = time % 2;
			if (time == 1){
				m_isCollision = true;
			}
		}
	}
	//setBltRect();
	if (type == "monster") {
		//Move();
		checkCollisionWithPlayer();
	}

	setIsCollision(bltCurPos.x, bltCurPos.y);

	if (isCollision()) {
		moveEnd();
	}
}


Point BulletBase::getAim()
{
	return this->m_aim;
}

bool BulletBase::isArrive()
{
	return m_isArrive;
}

void BulletBase::moveEnd()
{
	//m_isCollision = true;
	explodeAction();
	stopAllActions();
	this->setVisible(false);
	m_map->removeChild(this,true);
}

int BulletBase::getMagicCost()
{
	return m_magicCost;
}

void BulletBase::bindMonsterList(Vector<Monster*>monsterList)
{
	m_monsterList = monsterList;
}

void BulletBase::checkCollisionWithMonster()
{
	for (auto monster : m_monsterList) {
		if (monster->isAlive()){
			//Rect mstRect = Rect(monster->getPosition().x - 15, monster->getPosition().y - 15, 50, 50);
			if (monster->getBoundingBox().containsPoint(getPosition())) {
				//log("%f,%f", getPosition().x, getPosition().y);
				m_isCollision = true;
				monster->getHitted(m_attack + m_player->getAttack());
			}
		}
	}
}

void BulletBase::checkCollisionWithPlayer()
{
	if (m_player->getBoundingBox().containsPoint(getPosition())) {
		m_isCollision = true;
		m_player->hitted(m_attack);
	}
}

int BulletBase::getAttack()
{
	return m_attack;
}

void BulletBase::bindPlayer(Player* player)
{
	m_player = player;
}

void BulletBase::getDirection(float direction)
{
	m_direction = direction;
}

void BulletBase::Move()
{
	m_isCollision = false;
	Point bltCurPos = getTagPosition();
	//CC_DEGREES_TO_RADIANS(m_direction);
	setTagPosition(bltCurPos.x + m_speed * cos(CC_DEGREES_TO_RADIANS(m_direction)),
		           bltCurPos.y + m_speed * sin(CC_DEGREES_TO_RADIANS(m_direction)));
	//log("%f", m_direction);
	//log("%f,%f", cos(m_direction), sin(m_direction));
}

//Rect BulletBase::getBltRect()
//{
//	return bltRect;
//}

//void BulletBase::checkMonster()
//{
//	TMXObjectGroup* mstGroup = m_map->getObjectGroup("Monsters");
//
//}


void BulletBase::setUsed(bool isUsed)
{
	this->m_isUsed = isUsed;

	setVisible(isUsed);
}

bool BulletBase::isUsed()
{
	return this->m_isUsed;
}

bool BulletBase::isCollision()
{
	return m_isCollision;
}

void BulletBase::setIsCollision(int x, int y)
{
	//Rect bltRect = getBltRect();

	Size spriteSize = m_sprite->getContentSize();
	//log("x,y：%d,%d", x, y);

	Point dstPos = Point(x, y);
	


	Point tiledPos = tileCoordForPosition(Point(dstPos.x + 10, dstPos.y));
	//log("character position: %f,%f", tiledPos.x, tiledPos.y);
	

	//获取地图格子的唯一标识
	int tiledGid = meta->getTileGIDAt(tiledPos);
	//log("%d", tiledGid);

	//不为0，代表存在这个格子
	if (tiledGid != 0) {
		/*
		获取该地图格子的所有属性，目前我们只有一个Collidable属性
		格子是属于meta层的，但同时也是属于整个地图的，所以获取格子的所有属性
		时，通过格子唯一标识在地图中获得
		*/
		Value properties = m_map->getPropertiesForGID(tiledGid);

		ValueMap propertiesMap = properties.asValueMap();
		//取得格子的colliable属性值

		if (propertiesMap.find("Collidable") != propertiesMap.end()) {
			//取得格子的Collidable属性值
			Value prop = propertiesMap.at("Collidable");
			//判断Collidable值是否为true,如果是，则不让移动
			if (prop.asString().compare("true") == 0) {
				m_isCollision = true;
				
			}

		}
		if (propertiesMap.find("fence_wooden") != propertiesMap.end()) {
			//取得格子的Collidable属性值
			Value prop = propertiesMap.at("fence_wooden");
			//判断Collidable值是否为true,如果是，则不让移动
			if (prop.asString().compare("true") == 0) {
				m_isCollision = true;
			}

		}
		if (propertiesMap.find("food") != propertiesMap.end()) {
			Value prop = propertiesMap.at("food");
			//判断Collidable值是否为true,如果是，则不让移动
			if (prop.asString().compare("true") == 0) {
				m_isCollision = true;
				//this->showBlockBroken(tileCoord);
				meta->removeTileAt(tiledPos);
				//barrier_fence_ice->removeTileAt(tiledPos);
				wooden_case->removeTileAt(tiledPos);
				//return;
			}
		}
	}
}

//void BulletBase::setBltRect()
//{
//	bltRect = Rect(getPosition().x, getPosition().y, 50, 50);
//	//Rect bltRect = this->getBoundingBox();
//	//return bltRect;
//}




//********************************************
BulletGun::BulletGun()
{
	m_magicCost = 0;
	m_attack = 2;
	m_speed = 10.0f;

	type = "player";
}

BulletGun::~BulletGun()
{
}

bool BulletGun::init()
{
	bool bRet = false;
	do {
		Sprite* sprite = Sprite::create("Bullets/bulletGun.png");
		CC_BREAK_IF(!sprite);
		CC_BREAK_IF(!init(sprite));
		bRet = true;
	} while (0);
	start_time = clock();
	this->scheduleUpdate();

	return bRet;
}

//void BulletGun::update(float dt)
//{
//	Point bltCurPos = getTagPosition();
//
//	setIsCollision(bltCurPos.x, bltCurPos.y);
//
//	if (isCollision()) {
//		moveEnd();
//	}
//
//}

BulletGun* BulletGun::create(Sprite* sprite)
{
	BulletGun* bulletGun = new BulletGun();
	if (bulletGun && bulletGun->init(sprite)) {
		bulletGun->autorelease();
	}
	else {
		CC_SAFE_DELETE(bulletGun);
	}
	return bulletGun;

}

bool BulletGun::init(Sprite* sprite)
{
	bindSprite(sprite);
	return true;
}

//void BulletGun::onLockAim(Point aim)
//{
//	m_isCollision = false;
//	Point dstPos = this->getParent()->convertToNodeSpace(aim);
//
//	float distance = pow(dstPos.x - getPosition().x, 2) + pow(dstPos.y - getPosition().y, 2);
//
//	float speed = 25.0f;
//	float time = sqrt(distance / speed);
//
//	//aim为屏幕坐标，dstPos是屏幕坐标相对于子弹管理器的坐标
//
//
//	//log("%f,%f", dstPos.x, dstPos.y);
//	auto moveTo = MoveTo::create(time, dstPos);
//	//auto callFunc = CallFunc::create([&]() {
//	//	moveEnd();
//	//	});
//	//auto rorate = RotateTo::create(0.0f, deg);
//
//	auto actions = Sequence::create(moveTo, NULL);
//
//
//	this->runAction(actions);
//	for (int n = 0; n < 99; n++) {
//		this->runAction(actions->clone());
//	}
//}

void BulletGun::explodeAction()
{
	auto explode = Sprite::create("explodeGun.png");

	explode->setPosition(getPosition());

	auto scaleBy = ScaleBy::create(1.0f, 2.5f);
	auto fadeOut = FadeOut::create(1.0f);
	m_map->addChild(explode, 1);

	explode->runAction(scaleBy);
	explode->runAction(fadeOut);

}

//int BulletGun::getMagicCost()
//{
//	return m_magicCost;
//}



//void BulletGun::moveEnd()
//{
//	//m_isCollision = true;
//	stopAllActions();
//	this->setVisible(false);
//	this->removeChild(m_map);
//
//}











//**********************************************************************

BulletMstGun::BulletMstGun()
{
	m_attack = 3;
	type = "monster";
	m_speed = 2.5f;
}

BulletMstGun::~BulletMstGun()
{
}

bool BulletMstGun::init()
{
	bool bRet = false;
	do {
		Sprite* sprite = Sprite::create("Bullets/mstBulletGun.png");
		CC_BREAK_IF(!sprite);
		CC_BREAK_IF(!init(sprite));
		bRet = true;
	} while (0);
	start_time = clock();
	this->scheduleUpdate();

	return bRet;
}

BulletMstGun* BulletMstGun::create(Sprite* sprite)
{
	BulletMstGun* bulletMstGun = new BulletMstGun();
	if (bulletMstGun && bulletMstGun->init(sprite)) {
		bulletMstGun->autorelease();
	}
	else {
		CC_SAFE_DELETE(bulletMstGun);
	}
	return bulletMstGun;
}

bool BulletMstGun::init(Sprite* sprite)
{
	bindSprite(sprite);
	return true;
}

//void BulletMstGun::onLockAim(Point aim)
//
//{
//	m_isCollision = false;
//	Point dstPos = this->getParent()->convertToNodeSpace(aim);
//
//	float distance = pow(dstPos.x - getPosition().x, 2) + pow(dstPos.y - getPosition().y, 2);
//
//	float speed = 25.0f;
//	float time = sqrt(distance / speed);
//
//	//aim为屏幕坐标，dstPos是屏幕坐标相对于子弹管理器的坐标
//
//
//	//log("%f,%f", dstPos.x, dstPos.y);
//	auto moveTo = MoveTo::create(time, dstPos);
//	//auto callFunc = CallFunc::create([&]() {
//	//	moveEnd();
//	//	});
//	//auto rorate = RotateTo::create(0.0f, deg);
//
//	auto actions = Sequence::create(moveTo, NULL);
//
//
//	this->runAction(actions);
//	for (int n = 0; n < 99; n++) {
//		this->runAction(actions->clone());
//	}
//}

void BulletMstGun::explodeAction()

{
	auto explode = Sprite::create("explodeGun.png");

	explode->setPosition(getPosition());

	auto scaleBy = ScaleBy::create(1.0f, 2.5f);
	auto fadeOut = FadeOut::create(1.0f);
	m_map->addChild(explode, 1);

	explode->runAction(scaleBy);
	explode->runAction(fadeOut);

}



//*********************************************
BulletRedGun::BulletRedGun()
{
	m_magicCost = 2;
	m_attack = 7;
	m_speed = 9.0f;

	type = "player";
}

BulletRedGun::~BulletRedGun()
{
}

bool BulletRedGun::init()
{
	bool bRet = false;
	do {
		Sprite* sprite = Sprite::create("Bullets/bulletRedGun.png");
		CC_BREAK_IF(!sprite);
		CC_BREAK_IF(!init(sprite));
		bRet = true;
	} while (0);
	start_time = clock();
	this->scheduleUpdate();

	return bRet;
}

BulletRedGun* BulletRedGun::create(Sprite* sprite)
{
	BulletRedGun* bulletRedGun = new BulletRedGun();
	if (bulletRedGun && bulletRedGun->init(sprite)) {
		bulletRedGun->autorelease();
	}
	else {
		CC_SAFE_DELETE(bulletRedGun);
	}
	return bulletRedGun;
}

bool BulletRedGun::init(Sprite* sprite)
{
	bindSprite(sprite);
	return true;
}

void BulletRedGun::explodeAction()
{
	auto explode = Sprite::create("explodeGun.png");

	explode->setPosition(getPosition());

	explode->setContentSize(Size(80, 80));
	explode->setScale(0.8f);
	auto scaleBy = ScaleBy::create(1.0f, 1.0f,1.0f);
	auto fadeOut = FadeOut::create(1.0f);
	m_map->addChild(explode, 1);
	for (auto monster : m_monsterList) {
		if (explode->getBoundingBox().containsPoint(monster->getPosition())) {
			monster->getHitted(m_attack);
		}
	}
	explode->runAction(scaleBy);
	explode->runAction(fadeOut);
}


//**************************************************************
BulletShell::BulletShell()
{
	m_magicCost = 5;
	m_attack = 10;
	m_speed = 8.0f;

	type = "player";
}

BulletShell::~BulletShell()
{
}

bool BulletShell::init()
{
	bool bRet = false;
	do {
		Sprite* sprite = Sprite::create("Bullets/bulletShell.png");
		CC_BREAK_IF(!sprite);
		CC_BREAK_IF(!init(sprite));
		bRet = true;
	} while (0);
	start_time = clock();
	this->scheduleUpdate();

	return bRet;
}

BulletShell* BulletShell::create(Sprite* sprite)
{
	BulletShell* bulletShell = new BulletShell();
	if (bulletShell && bulletShell->init(sprite)) {
		bulletShell->autorelease();
	}
	else {
		CC_SAFE_DELETE(bulletShell);
	}
	return bulletShell;
}

bool BulletShell::init(Sprite* sprite)
{
	bindSprite(sprite);
	return true;
}

void BulletShell::explodeAction()
{
	auto explode = Sprite::create("explodeGun.png");

	explode->setPosition(getPosition());

	auto scaleBy = ScaleBy::create(1.0f, 8.0f, 8.0f);
	auto fadeOut = FadeOut::create(1.0f);
	m_map->addChild(explode, 1);

	explode->runAction(scaleBy);
	explode->runAction(fadeOut);
}



//****************************************************************
BulletKnife::BulletKnife()
{
	m_magicCost = 0;
	m_attack = 6;
	m_speed = 2.0f;

	type = "player_knife";
}

BulletKnife::~BulletKnife()
{
}

bool BulletKnife::init()
{
	bool bRet = false;
	do {
		Sprite* sprite = Sprite::create("Bullets/ability.png");
		CC_BREAK_IF(!sprite);
		CC_BREAK_IF(!init(sprite));
		bRet = true;
	} while (0);

	start_time = clock();

	this->scheduleUpdate();

	return bRet;
}

BulletKnife* BulletKnife::create(Sprite* sprite)
{
	BulletKnife* bulletKnife = new BulletKnife();
	if (bulletKnife && bulletKnife->init(sprite)) {
		bulletKnife->autorelease();
	}
	else {
		CC_SAFE_DELETE(bulletKnife);
	}
	return bulletKnife;
}

bool BulletKnife::init(Sprite* sprite)
{
	bindSprite(sprite);
	return true;
}

void BulletKnife::explodeAction()
{

}
