#pragma once
#ifndef _Scene_battleMap_H_
#define _Scene_battleMap_H_
#include "Player.h"
#include "cocos2d.h"
//#include "Controller_Move.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "GameTimer.h"
<<<<<<< Updated upstream
=======
#include "CoinBox.h"
#include "CoinLabel.h"
>>>>>>> Stashed changes
using namespace ui;
USING_NS_CC;
using namespace cocostudio;

/*��Ϸս������*/
class Scene_battleMap :public Layer
{
public:
	static Scene* createScene();   //��������


	CREATE_FUNC(Scene_battleMap);

	virtual bool init();

	virtual void update(float dt);

	void addPlayer(TMXTiledMap* map);//����ʿ�����ͼ

	void addPortal(TMXTiledMap* map);//�������ż����ͼ

	void addMonster(TMXTiledMap* map);//��ӹ���

	void addCoinBox(TMXTiledMap* map);//�������

	void addTimer();

	//void special_ground();   //����ذ��ϵ�������Ϊ
	void loadUI();

private:
	Player* m_player;
	GameTimer* m_timer;
<<<<<<< Updated upstream
=======
	CoinLabel* m_coinLabel;
>>>>>>> Stashed changes
	int num_money;
	LoadingBar* m_hpBar;
	LoadingBar* m_mpBar;
	LoadingBar* m_defendBar;
};

#endif
