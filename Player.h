#pragma once
#ifndef __INCLUDE_Player_H__
#define __INCLUDE_Player_H__

#include "HelloWorldScene.h"
#include "Controller_Move.h"
//#include "FlyWord.h"
#include "Characters.h"
#include <iostream>
#include "string"
#include "Weapons.h"
#include "BulletBase.h"
#include "Scene_battleMap.h"

#include "Monster.h"

#include "RecordData.h"

//class RecordData;

#include "Things.h"
class Things;
class Scene_battleMap;
class Portal;


//#include "Bullets.h"
//#include "BulletManager.h"

class Monster;   //�ȴӹ���ֻ���������Ϊ�������
class BulletBase;

// ����Ҫ
//class BulletGun;

using namespace std;
class Player :public Characters
{
public:
	CREATE_FUNC(Player);

	Player();
	virtual bool init();
	void run();
	void atk();
	//void run_left();

	virtual void update(float dt);
	

	void setViewPointByPlayer();

	virtual void setTagPosition(int x, int y);

	//void setTiledMap(TMXTiledMap* map);


	//void special_ground(int tiledGid);  //����ذ��ϵ��������
	Point pCollision(int x, int y);  //�����ƶ������ȡ��ײ��

	void addWeapon();
	void addKnife();
	void setBulletType(string bulletType);

	void loadBullet();//�ӵ����ţ�Ҳ��������ӵ�
	void bulletLogicCheck(float dt);
	void fire();
	float getDirection();
	void setDirection();  //������������

	//Rect getBltRect();


	void hitted(int attack);   //������
	int getiHP();   //Ѫ��
	int getiMP();
	int getDefence();
	int getSpeed();
	bool isAlive();
	int getAttack();

	void registeTouchEvent();

	void resetData();

	//void setBulletType(string type);
	string getBulletType();

	//BulletBase* getPBullet();

	//void setBltRect();
	//void getAim(Point aim);

	void bkBlue(int blue);
	void bkBlood(int blood);

	void addCoin(int addNum);
	int getCoin();
	void addBottle(bool redType);


	//�ӵ�ͼ�л�ȡMonsterList
	void getMonsterList(Vector<Monster*>m_monsterList);

	//Player* getPlayer();
	//void getDistanceWithMonster();
	//void fight();

private:
	//TMXTiledMap* m_map;
	
	//��������Ƿ��������ϰ���
	bool isJumping;

	float diatance_with_monster;

	//�����ײ�ĵ�ͼ��
	//TMXLayer* meta;
	//BulletManager* m_bulletMgr;

	////����������ת��Ϊ��ͼ��������
	//Point tileCoordForPosition(Point pos);
	//Rect bltRect;

	static int m_iHP;  //����Ѫ��
	static int m_defence;  //����ֵ
	static int m_iMp;
	static int m_speed;
	static int m_dfpower;//�������ܵ��˺����ڹ���������
	static int m_attack;
	static int m_coin;

	float m_degree;

	bool m_isAlive;

	Weapons* m_weapon;
	string m_bulletType;

	BulletBase* m_bullet;

	Point m_aim;

	static int m_bulletGrade;
	static int m_swordGrade;

	Vector<Monster*>mMonsterList;     //���������MonsterList����Ź�����ݸ��ӵ�

	//RecordData* recordData;

};


#endif