//#pragma once
//#ifndef _BulletManager_H_
//#define _BulletManager_H_
//#include "BulletBase.h"
//#include "Bullets.h"
//#include "cocos2d.h"
//
//using namespace cocos2d;
//
//class BulletManager :public Node {
//public:
//	BulletManager();
//	~BulletManager();
//	static BulletManager* create();
//	bool init();
//
//	//从缓存区获取一个未被使用的子弹
//	BulletBase* getAnyUnUsedBullet();
//private:
//	Vector<BulletBase*>m_bulletList;     //子弹列表
//
//	void createBullets();   //创建缓存子弹
//	void bulletLogicCheck(float dt);    //子弹逻辑
//	//BulletBase* getAnyUnUsedBullet();
//};
//
//
//#endif