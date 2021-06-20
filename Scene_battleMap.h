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

/*��Ϸս������*/
class Scene_battleMap :public Layer
{
public:
	//static Scene* createScene();   //��������

	//CREATE_FUNC(Scene_battleMap);

	//virtual bool init();

	virtual void update(float dt);

	void addPlayer(TMXTiledMap* map);//����ʿ�����ͼ

	void addPortal(TMXTiledMap* map);//�������ż����ͼ

	void addMonster(TMXTiledMap* map);//��ӹ���

	//void addMap();

	void addBox(TMXTiledMap* map);



	//void special_ground();   //����ذ��ϵ�������Ϊ
	void loadUI();

	void bottomUI();

	//Player* getPlayer();

	void registeKeyBoardEvent();

	//void  SetMap(string mapName);
	//string GetMap();

protected:

	Player* m_player;
	TMXTiledMap* map;

	Vector<Monster*>monsterList;  //�ȴ���һ��monsterList����Ź���

	

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
	static Scene* createScene();   //��������

	CREATE_FUNC(Scene_battleMap_1);

	virtual bool init();

};
class Scene_battleMap_2 :public Scene_battleMap 
{
public:
	static Scene* createScene();   //��������

	CREATE_FUNC(Scene_battleMap_2);

	

	virtual bool init();




private:
	
};


#endif
