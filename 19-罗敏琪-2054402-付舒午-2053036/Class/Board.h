#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_
#include "Characters.h"
class Board :
	public Characters
{
public:
	CREATE_FUNC(Board);
	virtual bool init();
	void act();
};

#endif _BOARD_H_