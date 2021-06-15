#pragma once
#ifndef _PLAYERBAR_H_
#define _PLAYERBAR_H_
#include "cocos2d.h"
#include "Player.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
using namespace ui;
using namespace cocos2d;
USING_NS_CC;

class PlayerBar:
	public Node
{
public:
	PlayerBar();
	~PlayerBar();
	CREATE_FUNC(PlayerBar);
	bool init();
	void update(float dt);
	void bindPlayer(Player* player);
	//void bindWeapon(Weapon* weapon );

private:
	Player* m_player;
	Sprite* bg_UI;
	LoadingBar* m_hpBar;
	LoadingBar* m_mpBar;
	LoadingBar* m_defendBar;

};

#endif // !_PLAYERBAR_H_