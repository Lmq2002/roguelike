
#include "SafeMap.h"

Scene* SafeMap::createScene()
{
    auto scene = Scene::create();
    auto layer = SafeMap::create();
    scene->addChild(layer);
    return scene;
}

SafeMap::SafeMap()
{
}


SafeMap::~SafeMap()
{
}

bool SafeMap::init()
{
    audio = SimpleAudioEngine::getInstance();
   /* if (audio->willPlayBackgroundMusic())
    {
        audio->resumeBackgroundMusic();
    }
    else
    {
        audio->playBackgroundMusic("menu.mp3",true);
    }*/
    if (audio->willPlayBackgroundMusic())
    {
        audio->resumeBackgroundMusic();
        log("bgmusic is playing!");
    }
    //暂停或正在播放 
    else if (audio->isBackgroundMusicPlaying())
    {
        audio->stopBackgroundMusic();
        audio->playBackgroundMusic("menu.mp3", true);
        //audio->setEffectsVolume(2.0f);
    }

    else
    {
        audio->playBackgroundMusic("menu.mp3", true);
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (!Layer::init())return false;

    TMXTiledMap* map = TMXTiledMap::create("safeMap.tmx");
    addChild(map);

    addPlayer(map);
    addPortal(map);
    addInfo(map);

    m_coinLabel = CoinLabel::create();
    m_coinLabel->bindPlayer(m_player);
    addChild(m_coinLabel);
    m_coinLabel->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - 20));

   // m_playerBar = PlayerBar::create();
  //  m_playerBar->bindPlayer(m_player);
   // m_playerBar->setPosition(Vec2(20, visibleSize.height - 10));
  //  addChild(m_playerBar);
   
    return true;
}

void SafeMap::update(float dt)
{
}

void SafeMap::addPortal(TMXTiledMap* map)
{
   Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* portalSprite = Sprite::create("portal_1.png");
    Portal* mPortal = Portal::create();
    mPortal->bindSprite(portalSprite);
    mPortal->act();
    mPortal->setScale(1.5f);

    TMXObjectGroup* objGroup = map->getObjectGroup("objects");
    ValueMap portalMap = objGroup->getObject("portal");
    float portalX = portalMap.at("x").asFloat();
    float portalY = portalMap.at("y").asFloat();
    mPortal->setPosition(Vec2(portalX, portalY));
    map->addChild(mPortal, 1);


}

void SafeMap::addPlayer(TMXTiledMap* map)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Sprite* playerSprite = Sprite::create("boy_run1.png");

    m_player = Player::create();
    m_player->bindSprite(playerSprite);

    m_player->scheduleUpdate();
    m_player->setTiledMap(map);

    TMXObjectGroup* objGroup = map->getObjectGroup("objects");
    ValueMap playerPointMap = objGroup->getObject("player");
    float playerX = playerPointMap.at("x").asFloat();
    float playerY = playerPointMap.at("y").asFloat();
    m_player->setPosition(Vec2(playerX, playerY));

    Controller_Move* controller_move = Controller_Move::create();
    controller_move->setiXSpeed(0);
    controller_move->setiYSpeed(0);
    addChild(controller_move);

    m_player->setController(controller_move);
    map->addChild(m_player,2);
}
//先做一个板
void SafeMap::addInfo(TMXTiledMap* map)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* infoBoard = Sprite::create("board1.png");
    Board* mBoard = Board::create();
    mBoard->bindSprite(infoBoard);
    mBoard->act();
    //mBoard->setScale(1.5f);

    TMXObjectGroup* objGroup = map->getObjectGroup("objects");
    ValueMap boardMap = objGroup->getObject("info");
    float boardX = boardMap.at("x").asFloat();
    float boardY = boardMap.at("y").asFloat();
    mBoard->setPosition(Vec2(boardX, boardY));
    map->addChild(mBoard, 1);
}
