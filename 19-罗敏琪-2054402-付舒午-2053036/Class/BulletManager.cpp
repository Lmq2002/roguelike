//#include "BulletManager.h"
//
//BulletManager::BulletManager()
//{
//}
//
//BulletManager::~BulletManager()
//{
//}
//
//BulletManager* BulletManager::create()
//{
//	BulletManager* bulletMgr = new BulletManager();
//	if (bulletMgr && bulletMgr->init()) {
//		bulletMgr->autorelease();
//	}
//	else {
//		CC_SAFE_DELETE(bulletMgr);
//	}
//	return bulletMgr;
//}
//
//bool BulletManager::init()
//{
//	//创建子弹对象
//	createBullets();
//
//	//循环检测子弹逻辑
//	this->schedule(schedule_selector(BulletManager::bulletLogicCheck),
//		BULLET_LOGIC_CHECK_INTERVAL);
//
//	return true;
//}
//
//BulletBase* BulletManager::getAnyUnUsedBullet()
//{
//	for (auto bullet : m_bulletList) {
//		if (bullet->isUsed() == false) {
//			bullet->setUsed(true);
//			return bullet;
//		}
//	}
//	return NULL;
//}
//
//void BulletManager::createBullets()
//{
//	BulletBase* bullet = NULL;
//	for (int i = 0; i < 10; i++) {
//		bullet = BulletGun::create();
//		//bullet->setPosition();
//
//		bullet->setUsed(false);
//		m_bulletList.pushBack(bullet);
//
//		this->addChild(bullet);
//
//	}
//}
//
//void BulletManager::bulletLogicCheck(float dt)
//{
//	for (auto bullet : m_bulletList) {
//		if (bullet->isUsed()) {
//			bullet->setUsed(false);
//		}
//	}
//}
