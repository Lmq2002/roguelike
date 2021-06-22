#pragma once
#ifndef _BulletBase_H_
#define _BulletBase_H_


#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180

#include "Characters.h"
#include <iostream>
#include "Monster.h"
/*Monster包含Player，而Player又包含了BulletBase*/
//所以现只需包含Player类即可,Player也需要包含Bulletbase
//*****************总之最后就是这三个类要互相包含

#include "Player.h"
//class BulletGun;

class Player;
class Monster;


class BulletBase :public Characters {
public:
	BulletBase();
	~BulletBase();

	virtual void update(float dt);

	Point getAim();  //获取攻击地点

	void setUsed(bool isUsed);   //设置子弹状态，是否可用

	bool isUsed();  //子弹是否可用

	bool isCollision();  //是否命中目标，即是否与其他物体碰撞
	void setIsCollision(int x, int y);//跟踪子弹是否碰撞

	//void setBltRect();

	//virtual void onLockAim(Point aim) = 0;  //子弹打过去
	//virtual void mstBulletMove() = 0;  //怪物子弹移动

	virtual void explodeAction() = 0;

	//可删
	bool isArrive(); //是否到达攻击目标

	void moveEnd();

	int getMagicCost();

	void bindMonsterList(Vector<Monster*>monsterList);

	void checkCollisionWithMonster();

	void checkCollisionWithPlayer();

	int getAttack();

	void bindPlayer(Player* player);

	void getDirection(float direction);
	//Rect getBltRect();
protected:

	Player* m_player;//绑定玩家对象

	bool m_isCollision;

	int m_magicCost;
	//可删
	bool m_isArrive;

	Vector<Monster*>m_monsterList;
	//Rect bltRect;

	int m_attack;  //枪的攻击力，所有子类都需要

	std::string type;



	void Move();
	float m_speed;

	float m_direction;


private:

	bool m_isUsed;  //标记是否已经在使用中
	Point m_aim;    //攻击目标




};

class BulletGun :public BulletBase {
public:
	BulletGun();
	~BulletGun();

	CREATE_FUNC(BulletGun);
	virtual bool init();

	/*virtual void update(float dt);*/

	static BulletGun* create(Sprite* sprite);
	bool init(Sprite* sprite);
	//virtual void onLockAim(Point aim);  //子弹打过去
	virtual void explodeAction();

	//int getMagicCost();

	

private:


	//void moveEnd();
};

class BulletKnife :public BulletBase{
public:
	BulletKnife();
	~BulletKnife();

	CREATE_FUNC(BulletKnife);
	virtual bool init();

	/*virtual void update(float dt);*/

	static BulletKnife* create(Sprite* sprite);
	bool init(Sprite* sprite);
	//virtual void onLockAim(Point aim);  //子弹打过去
	virtual void explodeAction();

	//int getMagicCost();


};

class BulletMstGun :public BulletBase{

public:
	BulletMstGun();
	~BulletMstGun();

	CREATE_FUNC(BulletMstGun);
	virtual bool init();

	static BulletMstGun* create(Sprite* sprite);
	bool init(Sprite* sprite);
	
	//virtual void onLockAim(Point aim);  //子弹打过去
	//virtual void mstBulletMove();
	

	virtual void explodeAction();


private:

};

class BulletRedGun :public BulletBase{
public:
	BulletRedGun();
	~BulletRedGun();

	CREATE_FUNC(BulletRedGun);
	virtual bool init();

	/*virtual void update(float dt);*/

	static BulletRedGun* create(Sprite* sprite);
	bool init(Sprite* sprite);
	//virtual void onLockAim(Point aim);  //子弹打过去
	virtual void explodeAction();

	//int getMagicCost();



private:
};

class BulletShell :public BulletBase {
public:
	BulletShell();
	~BulletShell();

	CREATE_FUNC(BulletShell);
	virtual bool init();

	/*virtual void update(float dt);*/

	static BulletShell* create(Sprite* sprite);
	bool init(Sprite* sprite);
	//virtual void onLockAim(Point aim);  //子弹打过去
	virtual void explodeAction();

	//int getMagicCost();


};

#endif
