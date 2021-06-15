#include "PlayerBar.h"

PlayerBar::PlayerBar()
{
}

PlayerBar::~PlayerBar()
{
}

bool PlayerBar::init()
{

	bg_UI = Sprite::create("menu_UI/background_UI.png");
	bg_UI->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	bg_UI->setScale(0.5f);
	addChild(bg_UI);

	m_hpBar = LoadingBar::create();
	m_hpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  
	m_hpBar->setPosition(Point(5, -10));  
	bg_UI->addChild(m_hpBar); 
	m_hpBar->loadTexture("menu_UI/PlayerHpUI.png"); 
	m_hpBar->setPercent(100);
	m_hpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_hpBar->setScale(0.5f);

	//»¤¶ÜÌõ
	m_mpBar = LoadingBar::create();
	m_mpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  
	m_mpBar->setPosition(Point(5,-40));  
	bg_UI->addChild(m_mpBar);  
	m_mpBar->loadTexture("menu_UI/PlayerMpUI.png"); 
	m_mpBar->setPercent(100);
	m_mpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_mpBar->setScale(0.5f);

	//À¶Ìõ
	m_defendBar = LoadingBar::create();
	m_defendBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  
	m_defendBar->setPosition(Point(5, - 24));  
	bg_UI->addChild(m_defendBar); 
	m_defendBar->loadTexture("menu_UI/PlayerDefendeseUI.png"); 
	m_defendBar->setPercent(100);
	m_defendBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_defendBar->setScale(0.5f);
	return true;
}

void PlayerBar::update(float dt)
{
	if (m_player)
	{
		m_defendBar->setPercent(m_player->getDefence() / 10.0f * 100);
		m_hpBar->setPercent(m_player->getiHP() / 10.0f * 100);
	}
}

void PlayerBar::bindPlayer(Player* player)
{
	m_player = player;
}
