#include "CoinLabel.h"

CoinLabel::CoinLabel()
{
	coinLabel = Label::createWithSystemFont("", "fonts/Marker Felt.ttf",12);
	coin = Sprite::create("coin.png");
	coin->setScale(0.6f);
	coin->setPosition(Vec2(-10, -3));
}

CoinLabel::~CoinLabel()
{
}

//CoinLabel* CoinLabel::createCoinLabel(Player* player)
//{
//	CoinLabel* tmpCoinLabel = new CoinLabel;
//	if (tmpCoinLabel && tmpCoinLabel->init())
//	{
//		tmpCoinLabel->autorelease();
//		
//		return tmpCoinLabel;
//	}
//	else
//	{
//		delete tmpCoinLabel;
//		tmpCoinLabel = NULL;
//	}
//	return NULL;
//}

bool CoinLabel::init()
{
	addChild(coinLabel);
	addChild(coin);
	schedule(CC_SCHEDULE_SELECTOR(CoinLabel::update));
	return true;
}

//int CoinLabel::getcoinNumber()
//{
//	return coinNumber;
//}
//
//void CoinLabel::addCoinNumber(int addNum)
//{
//	coinNumber += addNum;
//}

void CoinLabel::update(float dt)
{
	coinLabel->setString(Value(m_player->getCoin()).asString());
}

void CoinLabel::bindPlayer(Player* player)
{
	m_player = player;
}
