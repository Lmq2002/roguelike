#include "MessageBoard.h"
#include "extensions/cocos-ext.h"
#include "SafeMap.h"


USING_NS_CC;
USING_NS_CC_EXT;

//typedef std::function<void(cocos2d::Ref*, cocos2d::ui::ListView::EventType)> SEL_LISTVIEW;

MessageBoard::MessageBoard()
{

}

MessageBoard::~MessageBoard()
{
}

Scene* MessageBoard::createScene()
{
    Scene* scene = Scene::create();
    MessageBoard* tmpLayer = MessageBoard::create();
    scene->addChild(tmpLayer);
    return scene;
}

bool MessageBoard::init()
{
    if (!Layer::init())
    {
        return false;
  }
    m_iBeforeSel = 0;
    audio = SimpleAudioEngine::getInstance();
    
    if(audio->willPlayBackgroundMusic())
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

    auto bgSprite = Sprite::create("boardBG.png");
    bgSprite->setScale(2.0f);
    bgSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(bgSprite);

    //close button
    auto closeItem = Button::create("button/close_normal.png", "button/close_selected.png", "button/close_normal.png");
    closeItem->setScale(0.4f);
    closeItem->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            audio->playEffect("touch.mp3");
            break;
        case ui::Widget::TouchEventType::ENDED:
            audio->pauseBackgroundMusic();
            Director::getInstance()->replaceScene(SafeMap::createScene());
            break;
        default:
            break;
    }
    });
    closeItem->setPosition(Vec2(visibleSize.width-50,visibleSize.height-100));
    this->addChild(closeItem,2);

    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("info.plist", "info.png");
   
    //message
    m_monster1 = Sprite::createWithSpriteFrameName("monster1.png");
    m_monster1->setVisible(true);
    m_monster1->setPosition(Vec2(150,100));
    monster1 = Label::createWithSystemFont("striker : attack-3", "Marker Felt.ttf", 10);
    monster1->setColor(Color3B::BLACK);
    monster1->setVisible(true);
    monster1->setPosition(Vec2(150,40));

    m_monster2 = Sprite::createWithSpriteFrameName("monster2.png");
    m_monster2->setVisible(false);
    m_monster2->setPosition(Vec2(150, 100));
    monster2 = Label::createWithSystemFont("boar : attack-6", "Marker Felt.ttf", 10);
    monster2->setColor(Color3B::BLACK);
    monster2->setVisible(false);
    monster2->setPosition(Vec2(150, 40));

    m_weapon1 = Sprite::createWithSpriteFrameName("weapon1.png");
    m_weapon1->setVisible(false);
    m_weapon1->setPosition(Vec2(150,100));
    weapon1 = Label::createWithSystemFont("gun attack--", "Marker Felt.ttf", 10);
    weapon1->setColor(Color3B::BLACK);
    weapon1->setVisible(false);
    weapon1->setPosition(Vec2(150,40));



    bgSprite->addChild(m_monster1);
    bgSprite->addChild(monster1);
    bgSprite->addChild(m_weapon1);
    bgSprite->addChild(weapon1);
    bgSprite->addChild(m_monster2);
    bgSprite->addChild(monster2);

  

    //monster button 
    Button* monster = Button::create("monster1.png", "monster1.png");
    monster->setName("monster");
    monster->setScale9Enabled(true);
   // monster->setSizeType(default_button->getSizeType());
    Layout* custom_item = Layout::create();
    //custom_item->setSizeType(monster->getSizeType());
    monster->setPosition(Vec2(20,visibleSize.height-100));
    custom_item->addChild(monster);
    monster->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                audio->playEffect("touch.mp3");
                break;
            case ui::Widget::TouchEventType::ENDED:
                m_monster1->setVisible(true);
                monster1->setVisible(true);
                m_weapon1->setVisible(false);
                weapon1->setVisible(false);
                m_monster2->setVisible(false);
                monster2->setVisible(false);
                break;
            default:
                break;
        }
        });
    addChild(custom_item);


    //monster2
    Button* monster_2 = Button::create("monster2.png", "monster2.png");
    monster_2->setName("monster2");
    monster_2->setScale9Enabled(true);
    Layout* custom_item_2 = Layout::create();
    monster_2->setPosition(Vec2(20, visibleSize.height - 150));
    custom_item_2->addChild(monster_2);
    monster_2->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                audio->playEffect("touch.mp3");
                break;
            case ui::Widget::TouchEventType::ENDED:
                m_monster1->setVisible(false);
                monster1->setVisible(false);
                m_weapon1->setVisible(false);
                weapon1->setVisible(false);
                m_monster2->setVisible(true);
                monster2->setVisible(true);
                break;
            default:
                break;
        }
        });
    addChild(custom_item_2);


    //weapon button
    Button* weapon = Button::create("weapon1.png", "weapon1.png");
    weapon->setName("weapon");
    weapon->setScale9Enabled(true);
   // weapon->setSizeType(default_button->getSizeType());
    Layout* custom_item1 = Layout::create();
   // custom_item1->setSizeType(weapon->getSizeType());
    weapon->setPosition(Vec2(20, visibleSize.height - 200));
    custom_item->addChild(weapon);
    weapon->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                audio->playEffect("touch.mp3");
                break;
            case ui::Widget::TouchEventType::ENDED:
                m_monster1->setVisible(false);
                monster1->setVisible(false);
                m_weapon1->setVisible(true);
                weapon1->setVisible(true);
                m_monster2->setVisible(false);
                monster2->setVisible(false);
                break;
            default:
                break;
        }
        });
    addChild(custom_item1);

   // listView->pushBackCustomItem(custom_item);
   // listView->pushBackCustomItem(custom_item1);

    return true;
}
//void MessageBoard::SelectedItemEvent(Ref* pSender, ListView::TouchEventType type)
//{
//    ListView* listView = static_cast<ListView*>(pSender);
//    CC_UNUSED_PARAM(listView);
//    m_iBeforeSel = listView->getCurSelectedIndex();
//
//    switch (m_iBeforeSel)
//    {
//        case 0:
//            m_monster1->setVisible(true);
//            monster1->setVisible(true);
//            weapon1->setVisible(false);
//            m_weapon1->setVisible(false);
//            break;
//        case 1:
//            m_monster1->setVisible(false);
//            monster1->setVisible(false);
//            weapon1->setVisible(true);
//            m_weapon1->setVisible(true);
//            break;
//        default: 
//            break;
//    }
//}
////音乐滑动条
//auto slider = Slider::create();
//slider->loadBarTexture("Slider_Back.png"); // what the slider looks like
//slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
//slider->loadProgressBarTexture("Slider_PressBar.png");
//slider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
//    switch (type)
//    {
//        case ui::Widget::TouchEventType::BEGAN:
//            break;
//        case ui::Widget::TouchEventType::ENDED:
//            break;
//        case ui::Widget::TouchEventType::MOVED:
//            //没想好
//            break;
//        default:
//            break;
//    }
//    });
//this->addChild(slider);
//slider->setPosition(Vec2(20, 50));
//
////音效滑动条
//auto effectSlider = Slider::create();
//effectSlider->loadBarTexture("Slider_Back.png"); // what the slider looks like
//effectSlider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
//effectSlider->loadProgressBarTexture("Slider_PressBar.png");
//effectSlider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
//    switch (type)
//    {
//        case ui::Widget::TouchEventType::BEGAN:
//            break;
//        case ui::Widget::TouchEventType::ENDED:
//            break;
//        case ui::Widget::TouchEventType::MOVED:
//            //没想好
//            break;
//        default:
//            break;
//    }
//    });
//this->addChild(effectSlider);
//effectSlider->setPosition(Vec2(20, 50));
//
////回SafeMap按钮
//auto button1 = Button::create("normal_image.png", "selected_image.png", "disabled_image.png");
//button1->setTitleText("Button Text");
//button1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
//    switch (type)
//    {
//        case ui::Widget::TouchEventType::BEGAN:
//            break;
//        case ui::Widget::TouchEventType::ENDED:
//            Director::getInstance()->replaceScene(SafeMap::createScene());
//            break;
//        default:
//            break;
//    }
//    });
//this->addChild(button1);
//
////继续按钮
//auto button2 = Button::create("normal_image.png", "selected_image.png", "disabled_image.png");
//button2->setTitleText("Button Text");
//button2->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
//    switch (type)
//    {
//        case ui::Widget::TouchEventType::BEGAN:
//            break;
//        case ui::Widget::TouchEventType::ENDED:
//
//            break;
//        default:
//            break;
//    }
//    });
//this->addChild(button2);
//
//
//return false;