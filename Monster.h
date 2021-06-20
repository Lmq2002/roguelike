#pragma once
#ifndef _Monster_H_
#define _Monster_H_
#include "Characters.h"
#include "Player.h"
//#include "Bullets.h"
#include "BulletBase.h"
class BulletBase;
class Player;   //�ȴӹ���ֻ���������Ϊ�������
class BulletGun;

class Monster :public Characters {
public:
	//Monster();
	//~Monster();
	//CREATE_FUNC(Monster);
	//virtual bool init();
	virtual void update(float dt); //��дupdate����

	void show();  //��ʾ����
	
	void setTiledMapPosition(Point position); 
	bool isAlive();//�ж��Ƿ�״̬

	//�Ƿ�����ս������Χ
	//�����ײ����
	//bool isCollideWithBullet();
	//bool hitted(int attack);  //��������
	//bool ifHittedByBullet();

	//����Ҷ���
	void bindPlayer(Player* player);

	void hide();

	virtual void setTagPosition(int x, int y);

	void getHitted(int attack);

	virtual void Attack() = 0;

	void setDegree();//���ù��﷢���ӵ��ķ���

	void getDistanceWithPlayer();

	bool collisionWithPlayer();

	
	

protected:



	bool m_isAlive;
	Player* m_player;
	int type;

	int m_hp;
	int m_attack;
	int bkBlue;

	float distance_with_player;

	int move_x;
	int move_y;

	float m_degree;

	bool isAttacked;

	//Vector<BulletBase*>bulletList;
	BulletBase* m_bullet;

	int record_time_mstAttack = 0;
	int m_attackNum;

	float shot_direction = 0;//ɢ������

};


class MonsterStriker :public Monster{
public:
	MonsterStriker();
	~MonsterStriker();

	CREATE_FUNC(MonsterStriker);

	virtual bool init();

	virtual void Attack();


};

class MonsterPig :public Monster {
public:
	MonsterPig();
	~MonsterPig();

	CREATE_FUNC(MonsterPig);

	virtual bool init();

	virtual void Attack();

private:
	
};

#endif