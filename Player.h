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

class Monster;   //先从怪物只包含人物，改为互相包含
class BulletBase;

// 不需要
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


	//void special_ground(int tiledGid);  //特殊地板上的特殊操作
	Point pCollision(int x, int y);  //根据移动方向获取碰撞点

	void addWeapon();
	void addKnife();
	void setBulletType(string bulletType);

	void loadBullet();//子弹上膛，也就是添加子弹
	void bulletLogicCheck(float dt);
	void fire();
	float getDirection();
	void setDirection();  //设置武器朝向

	//Rect getBltRect();


	void hitted(int attack);   //被攻击
	int getiHP();   //血条
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


	//从地图中获取MonsterList
	void getMonsterList(Vector<Monster*>m_monsterList);

	//Player* getPlayer();
	//void getDistanceWithMonster();
	//void fight();

private:
	//TMXTiledMap* m_map;
	
	//标记主角是否碰到了障碍物
	bool isJumping;

	float diatance_with_monster;

	//检测碰撞的地图层
	//TMXLayer* meta;
	//BulletManager* m_bulletMgr;

	////将像素坐标转换为地图格子坐标
	//Point tileCoordForPosition(Point pos);
	//Rect bltRect;

	static int m_iHP;  //主角血量
	static int m_defence;  //护盾值
	static int m_iMp;
	static int m_speed;
	static int m_dfpower;//防御，受到伤害等于攻击减防御
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

	Vector<Monster*>mMonsterList;     //创建人物的MonsterList，存放怪物，传递给子弹

	//RecordData* recordData;

};


#endif