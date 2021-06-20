//#include "Bullets.h"
//
//BulletGun::BulletGun()
//{
//	m_magicCost = 1;
//}
//
//BulletGun::~BulletGun()
//{
//}
//
//bool BulletGun::init()
//{
//	bool bRet = false;
//	do {
//		Sprite* sprite = Sprite::create("Bullets/bulletGun.png");
//		CC_BREAK_IF(!sprite);
//		CC_BREAK_IF(!init(sprite));
//		bRet = true;
//	} while (0);
//
//	this->scheduleUpdate();
//
//	return bRet;
//}
//
////void BulletGun::update(float dt)
////{
////	Point bltCurPos = getTagPosition();
////
////	setIsCollision(bltCurPos.x, bltCurPos.y);
////
////	if (isCollision()) {
////		moveEnd();
////	}
////
////}
//
//BulletGun* BulletGun::create(Sprite* sprite)
//{
//	BulletGun* bulletGun = new BulletGun();
//	if (bulletGun && bulletGun->init(sprite)) {
//		bulletGun->autorelease();
//	}
//	else {
//		CC_SAFE_DELETE(bulletGun);
//	}
//	return bulletGun;
//
//}
//
//bool BulletGun::init(Sprite* sprite)
//{
//	bindSprite(sprite);
//	return true;
//}
//
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
//
////int BulletGun::getMagicCost()
////{
////	return m_magicCost;
////}
//
//
//
////void BulletGun::moveEnd()
////{
////	//m_isCollision = true;
////	stopAllActions();
////	this->setVisible(false);
////	this->removeChild(m_map);
////
////}
