#pragma once
#ifndef _SAFEMAP_H_
#define _SAFEMAP_H_
#include "cocos2d.h"
#include "Player.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "CoinLabel.h"
#include "Portal.h"
//#include "PlayerBar.h"
#include "Board.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"

using namespace ui;
using namespace cocostudio;
using namespace cocos2d;
using namespace CocosDenshion;
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
	SimpleAudioEngine* audio;
	Player* m_player;
	CoinLabel* m_coinLabel;
	//LoadingBar* m_hpBar;
	//PlayerBar* m_playerBar;


};
#endif // !_SAFEMAP_H_