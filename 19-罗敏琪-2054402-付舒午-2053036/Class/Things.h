#pragma once
#ifndef _Things_H_
#define _Things_H_

#include "Characters.h"
#include "Player.h"

class Player;

class Things :public Characters {
public:
	Things();
	~Things();

	void bindPlayer(Player* player);

	void setDistanceWithPlayer();

	float getDistanceWithPlayer();

protected:

	bool m_isUsed;

	Player* m_player;

	float distance_with_player;

};


#endif