#pragma once
#ifndef _BulletBase_H_
#define _BulletBase_H_


#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180

#include "Characters.h"
#include <iostream>
#include "Monster.h"
/*Monster����Player����Player�ְ�����BulletBase*/
//������ֻ�����Player�༴��,PlayerҲ��Ҫ����Bulletbase
//*****************��֮��������������Ҫ�������

#include "Player.h"
//class BulletGun;

class Player;
class Monster;


class BulletBase :public Characters {
public:
	BulletBase();
	~BulletBase();

	virtual void update(float dt);

	Point getAim();  //��ȡ�����ص�

	void setUsed(bool isUsed);   //�����ӵ�״̬���Ƿ����

	bool isUsed();  //�ӵ��Ƿ����

	bool isCollision();  //�Ƿ�����Ŀ�꣬���Ƿ�������������ײ
	void setIsCollision(int x, int y);//�����ӵ��Ƿ���ײ

	//void setBltRect();

	//virtual void onLockAim(Point aim) = 0;  //�ӵ����ȥ
	//virtual void mstBulletMove() = 0;  //�����ӵ��ƶ�

	virtual void explodeAction() = 0;

	//��ɾ
	bool isArrive(); //�Ƿ񵽴﹥��Ŀ��

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

	Player* m_player;//����Ҷ���

	bool m_isCollision;

	int m_magicCost;
	//��ɾ
	bool m_isArrive;

	Vector<Monster*>m_monsterList;
	//Rect bltRect;

	int m_attack;  //ǹ�Ĺ��������������඼��Ҫ

	std::string type;



	void Move();
	float m_speed;

	float m_direction;


private:

	bool m_isUsed;  //����Ƿ��Ѿ���ʹ����
	Point m_aim;    //����Ŀ��




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
	//virtual void onLockAim(Point aim);  //�ӵ����ȥ
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
	//virtual void onLockAim(Point aim);  //�ӵ����ȥ
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
	
	//virtual void onLockAim(Point aim);  //�ӵ����ȥ
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
	//virtual void onLockAim(Point aim);  //�ӵ����ȥ
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
	//virtual void onLockAim(Point aim);  //�ӵ����ȥ
	virtual void explodeAction();

	//int getMagicCost();


};

#endif
