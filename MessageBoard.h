#pragma once
#ifndef _MESSAGEBOARD_H_
#define _MESSAGEBOARD_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;

class MessageBoard :
	public Layer
{
public:	
	MessageBoard();
	~MessageBoard();
	CREATE_FUNC(MessageBoard);
	static Scene* createScene();
	virtual bool init();


//	void menuTurnToSafe(Ref* pSender);
	ListView* listView;
	//void SelectedItemEvent(/*Ref* pSender,*/ ListView::EventType type);
	/*void SelectedItemEvent(Ref* pSender, ListView::TouchEventType type);*/

private:
	size_t m_iBeforeSel;
	Sprite* m_monster1;
	Label* monster1;
	Sprite* m_monster2;
	Label* monster2;
	Sprite* m_weapon1;
	Label* weapon1;
	
	SimpleAudioEngine* audio;

};
#endif

