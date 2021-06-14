#include "GameTimer.h"
USING_NS_CC;

float GameTimer::pTime = 0.0f;
GameTimer::GameTimer()
{
	//label = Label::createWithSystemFont("", "fonts/Marker Felt.tt", 10);

}

GameTimer::~GameTimer()
{
}

GameTimer* GameTimer::createTimer()
{
	GameTimer* gameTimer = new GameTimer;
	if (gameTimer && gameTimer->init())
	{
		gameTimer->autorelease();
		return gameTimer;
	}
	else
	{
		delete gameTimer;
		gameTimer = NULL;
	}
	return NULL;
}

void GameTimer::update(float dt)
{
	pTime = pTime+0.01f;
//	auto label = Label::createWithTTF("0","fonts/arial.ttf",32);
	/*if (label)
	{
		label->setString(Value((int)pTime).asString());
		label->setPosition(10,50);*/
		//log("%f", pTime);
		/*log("label position:(%f,%f)", label->getPosition().x, label->getPosition().y);
		log("%s",label->getString());
	}*/
	/*else
	{
		log("no label!");
	}*/
	
	
	
}

bool GameTimer::init()
{
	
	schedule(CC_SCHEDULE_SELECTOR(GameTimer::update), 0.01f);
	log("%f", pTime);
	//label->setPosition(Vec2(10,50));
	//addChild(label,1);
	return true;
}

void GameTimer::stop()
{
	unschedule(CC_SCHEDULE_SELECTOR(GameTimer::update));
}

float GameTimer::getTime()
{
	return pTime;
}

