#pragma once
#ifndef _Scene_battleMap_H_
#define _Scene_battleMap_H_
#include "Player.h"
#include "cocos2d.h"
//#include "Controller_Move.h"
#include "Controller_Move.h"
#include "Characters.h"
#include "Portal.h"
#include "Monster.h"
#include "Weapons.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "CoinBox.h"
#include "CoinLabel.h"

class CoinLabel;

using namespace CocosDenshion;

//#include "Scene_battleMap_2.h"

//class Scene_battleMap_2;
class Player;
class Monster;
class Portal;

using namespace ui;
USING_NS_CC;
using namespace cocostudio;

//static Player* m_player;
//class Monster;
// Player* m_player;

/*游戏战斗界面*/
class Scene_battleMap :public Layer
{
public:
	//static Scene* createScene();   //创建场景

	//CREATE_FUNC(Scene_battleMap);

	//virtual bool init();

	virtual void update(float dt);

	void addPlayer(TMXTiledMap* map);//将骑士加入地图

	void addPortal(TMXTiledMap* map);//将传送门加入地图

	void addMonster(TMXTiledMap* map);//添加怪物

	//void addMap();

	void addBox(TMXTiledMap* map);



	//void special_ground();   //特殊地板上的特殊行为
	void loadUI();

	void bottomUI();

	//Player* getPlayer();

	void registeKeyBoardEvent();

	//void  SetMap(string mapName);
	//string GetMap();

protected:

	Player* m_player;
	TMXTiledMap* map;

	Vector<Monster*>monsterList;  //先创建一个monsterList，存放怪物

	

	//ValueVector mstArray;
	//TMXObjectGroup* mstGroup;
	Portal* mPortal;

	int num_money;
	LoadingBar* m_hpBar;
	LoadingBar* m_mpBar;
	LoadingBar* m_defendBar;

	CoinLabel* m_coinLabel;

};


class Scene_battleMap_1 :public Scene_battleMap{
public:
	static Scene* createScene();   //创建场景

	CREATE_FUNC(Scene_battleMap_1);

	virtual bool init();

};
class Scene_battleMap_2 :public Scene_battleMap 
{
public:
	static Scene* createScene();   //创建场景

	CREATE_FUNC(Scene_battleMap_2);

	

	virtual bool init();




private:
	
};


#endif
