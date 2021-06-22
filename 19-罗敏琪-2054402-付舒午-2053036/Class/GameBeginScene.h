#pragma once
#ifndef _GAMEBEGINSCENE_H_
#define _GAMEBEGINSCENE_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "SafeMap.h"
using namespace cocos2d;
//using namespace CocosDenshion; 
using namespace ui;
USING_NS_CC;

class GameBeginScene:
	public Layer
{
public:
	CREATE_FUNC(GameBeginScene);
	static Scene* createScene();
	bool init();
	void startNewGame(cocos2d::Ref* pSender);
	void exitMyGame(cocos2d::Ref* pSender);
	void addVolume(cocos2d::Ref* pSender);
	void subVolume(cocos2d::Ref* pSender);
private:
	SimpleAudioEngine* audio;

};

#endif // !_GAMEBEGINSCENE_H_