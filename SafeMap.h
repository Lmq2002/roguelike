#pragma once
#ifndef _SAFEMAP_H_
#define _SAFEMAP_H_
#include "cocos2d.h"
#include "Player.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "CoinLabel.h"
#include "Portal.h"


using namespace ui;
using namespace cocostudio;
using namespace cocos2d;
USING_NS_CC;


class SafeMap :
	public Layer
{
public:
	SafeMap();
	~SafeMap();
	static Scene* createScene();
	CREATE_FUNC(SafeMap);
	bool init();
	void update(float dt);
	void addPlayer(TMXTiledMap* map);
	void addPortal(TMXTiledMap* map);
	void addInfo(TMXTiledMap* map);
private:
	Player* m_player;
	CoinLabel* m_coinLabel;
	//LoadingBar* m_hpBar;


};
#endif // !_SAFEMAP_H_