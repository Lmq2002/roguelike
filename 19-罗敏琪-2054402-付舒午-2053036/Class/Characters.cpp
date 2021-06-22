#include "Characters.h"

void Characters::bindSprite(Sprite* sprite)
{
	this->m_sprite = sprite;
	this->addChild(m_sprite);

	Size size = m_sprite->getContentSize();
	this->setContentSize(size);
}

Sprite* Characters::getSprite()
{
	return this->m_sprite;
}

void Characters::setController(mController* controller)
{
	this->m_controller = controller;

	m_controller->setControllerListener(this);
}

void Characters::setTagPosition(int x, int y)
{
	setPosition(Point(x, y));
}

Point Characters::getTagPosition()
{
	return getPosition();
}

void Characters::setTiledMap(TMXTiledMap* map)
{
	this->m_map = map;

	//����metaͼ�������
	this->meta = m_map->getLayer("meta");
	this->wooden_case = m_map->getLayer("wooden_case");
	this->meta->setVisible(false);    //��Ҫ��ʾ
	//this->barrier_fence_ice = m_map->getLayer("barrier_fence_ice");

}

Point Characters::tileCoordForPosition(Point pos)
{

	//log("%d", tiledSize.width);
	int x = pos.x / m_map->getContentSize().width * m_map->getMapSize().width;
	int y = m_map->getMapSize().height - pos.y / m_map->getContentSize().height * m_map->getMapSize().height;

	//cocos2d-x��Ĭ��Y�������������ϵģ�����Ҫ��һ���������
	//log("getMapSize:%f, %f", mapTiledNum.width, mapTiledNum.height);
	//log("getTileSize:%f, %f", tiledSize.width, tiledSize.height);
	//����������㿪ʼ����
	if (x > 0) {
		x -= 1;
	}
	if (y > 0) {
		y -= 0;
	}

	//log("%d,%d", x, y);
	return Point(x, y);
}
