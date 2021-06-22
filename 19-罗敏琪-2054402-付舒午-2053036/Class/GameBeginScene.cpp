#include "GameBeginScene.h"

Scene* GameBeginScene::createScene()
{
    Scene* scene = Scene::create();
    GameBeginScene* layer = GameBeginScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameBeginScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    audio = SimpleAudioEngine::getInstance();
    if (!audio->isBackgroundMusicPlaying())
    {
        audio->stopBackgroundMusic();
    }
    audio->playBackgroundMusic("menu.mp3", 1);

    Size visibleSize = Director::getInstance()->getWinSize();

    auto bgSprite = Sprite::create("beginMenu.png");
    bgSprite->setPosition(visibleSize / 2);
    addChild(bgSprite);

    auto start = Label::createWithTTF( "start new game","fonts/Marker Felt.ttf", 30);
    start->setTextColor(Color4B::WHITE);
    auto startItem = MenuItemLabel::create(start, CC_CALLBACK_1(GameBeginScene::startNewGame, this));
    auto close = Label::createWithTTF( "exit","fonts/Marker Felt.ttf", 30);
    close->setTextColor(Color4B::WHITE);
    auto closeItem = MenuItemLabel::create(close, CC_CALLBACK_1(GameBeginScene::exitMyGame, this));

    auto addVolume = Label::createWithTTF("+", "fonts/Marker Felt.ttf", 20);
    addVolume->setTextColor(Color4B::WHITE);
    auto addItem = MenuItemLabel::create(addVolume, CC_CALLBACK_1(GameBeginScene::addVolume, this));
    
    auto subVolume = Label::createWithTTF("-", "fonts/Marker Felt.ttf", 20);
    subVolume->setTextColor(Color4B::WHITE);
    auto subItem = MenuItemLabel::create(subVolume, CC_CALLBACK_1(GameBeginScene::subVolume, this));


    auto menu = Menu::create(startItem, closeItem,addItem,subItem, NULL);
    startItem->setPosition(-100, -20);
    closeItem->setPosition(-100, -60);
    addItem->setPosition(100,50);
    subItem->setPosition(80, 50);
    addChild(menu);
       
    auto volume = Label::createWithTTF("Volume", "fonts/Marker Felt.ttf", 20);
    volume->setPosition(270, 210);
    volume->setTextColor(Color4B::WHITE);
    addChild(volume);
    return true;
    
}

void GameBeginScene::startNewGame(cocos2d::Ref* pSender)
{
    audio->pauseBackgroundMusic();
    Director::getInstance()->pushScene(SafeMap::createScene());
}

void GameBeginScene::exitMyGame(cocos2d::Ref* pSender)
{
    audio->stopAllEffects();
    Director::getInstance()->end();
}

void GameBeginScene::addVolume(cocos2d::Ref* pSender)
{
    audio->setBackgroundMusicVolume(audio->getBackgroundMusicVolume() + 0.1f);
    audio->setEffectsVolume(audio->getEffectsVolume() + 0.1f);
    audio->playEffect("touch.mp3");
    log("volume %f", audio->getBackgroundMusicVolume());
}

void GameBeginScene::subVolume(cocos2d::Ref* pSender)
{
    if (audio->getBackgroundMusicVolume() > 0.1f)
    {
        audio->setBackgroundMusicVolume(audio->getBackgroundMusicVolume() - 0.1f);
    }
    if(audio->getEffectsVolume()>0.1f)
    audio->setEffectsVolume(audio->getEffectsVolume() - 0.1f);
    audio->playEffect("touch.mp3");
    log("volume %f", audio->getBackgroundMusicVolume());
}
