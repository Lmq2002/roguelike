#include "Things.h"

Things::Things()
{
	m_isUsed = false;
}

Things::~Things()
{
}

void Things::bindPlayer(Player* player)
{
	m_player = player;
}

void Things::setDistanceWithPlayer()
{
	float distance = pow(m_player->getPosition().x - getPosition().x, 2) +
		pow(m_player->getPosition().y - getPosition().y, 2);
	distance_with_player = sqrt(distance);
}

float Things::getDistanceWithPlayer()
{
	return distance_with_player;
}
