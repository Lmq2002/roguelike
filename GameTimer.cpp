#include "GameTimer.h"
USING_NS_CC;

float GameTimer::pTime = 0.0f;
//Label* GameTimer::label = new Label;
//Label* GameTimer::label = Label::createWithTTF("0.00","arial.ttf",30);
//Label* GameTimer::
//Label* GameTimer::label = Label::createWithSystemFont("my text", "Marker Felt", 24);
//Label* GameTimer::label = Label::create();

//MenuItemLabel* GameTimer::menuLabel = MenuItemLabel::create(label,NULL);
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
	pTime = pTime+1.00f;
//	auto label = Label::createWithTTF("0","fonts/arial.ttf",32);
	/*if (label)
	{
		label->setString(Value((int)pTime).asString());
		label->setPosition(10,50);*/
		log("%f", pTime);
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
	
	schedule(CC_SCHEDULE_SELECTOR(GameTimer::update), 1.00f);
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

