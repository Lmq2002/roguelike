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
//	//�ӻ�������ȡһ��δ��ʹ�õ��ӵ�
//	BulletBase* getAnyUnUsedBullet();
//private:
//	Vector<BulletBase*>m_bulletList;     //�ӵ��б�
//
//	void createBullets();   //���������ӵ�
//	void bulletLogicCheck(float dt);    //�ӵ��߼�
//	//BulletBase* getAnyUnUsedBullet();
//};
//
//
//#endif