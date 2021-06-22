#include "Board.h"

bool Board::init()
{
    return true;
}

void Board::act()
{
    SpriteFrameCache* frameCache=SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("board.plist", "board.png");
    auto cache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*>frameList;
    frameList.pushBack(cache->getSpriteFrameByName("board1.png"));
    frameList.pushBack(cache->getSpriteFrameByName("board2.png"));

    Animation* animation = Animation::createWithSpriteFrames(frameList);
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.1f);

    Animate* animate = Animate::create(animation);

    m_sprite->runAction(animate);


}
