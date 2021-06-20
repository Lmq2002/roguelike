#pragma once
#ifndef _Portal_H_
#define _Portal_H_
#include "Characters.h"
#include "Player.h"

//using namespace cocos2d;
class Player;

class Portal : public Characters {
public:
	CREATE_FUNC(Portal);
	virtual bool init();
	void act();
	//void setTiledMap(TMXTiledMap* map);

	virtual void update(float dt);
	bool isCollisionWithPlayer();

	void bindPlayer(Player* player);
	int type;

private:
	//TMXTiledMap* m_map;
	Player* m_player;
	
};


#endif