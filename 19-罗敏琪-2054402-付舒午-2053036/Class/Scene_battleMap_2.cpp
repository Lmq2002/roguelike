//#include "Scene_battleMap_2.h"
//
//Scene* Scene_battleMap_2::createScene()
//{
//	auto scene = Scene::create();
//	auto layer = Scene_battleMap_2::create();
//
//
//	scene->addChild(layer);
//
//	return scene;
//}
//
//void Scene_battleMap_2::onEnter()
//{
//	
//}
//
//bool Scene_battleMap_2::init()
//{
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	if (!Layer::init())return false;
//
//	Sprite* bg_UI = Sprite::create("menu_UI/background_UI.png");
//	bg_UI->setPosition(Point(0, visibleSize.height));
//	bg_UI->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
//	bg_UI->setScale(0.5f);
//	this->addChild(bg_UI, 2);
//
//	loadUI();
//
//	this->scheduleUpdate();
//
//	/*加载Tiled地图，添加到场景中*/
//	TMXTiledMap* map = TMXTiledMap::create("BattleMap_ice_2.tmx");
//	
//
//	this->addChild(map);
//
//
//	addPlayer(map);  //加载骑士
//	
//
//	return true;
//}
//
//void Scene_battleMap_2::update(float dt)
//{
//	m_defendBar->setPercent(m_player->getDefence() / 10.0f * 100);
//	m_hpBar->setPercent(m_player->getiHP() / 10.0f * 100);
//	m_mpBar->setPercent(m_player->getiMP() / 200.0f * 100);
//	//log("Hp: %d", m_player->getiHP());
//
//	if (!m_player->isAlive())
//	{
//		m_player->setVisible(false);
//		Director::getInstance()->replaceScene(HelloWorld::createScene());
//	}
//}
//
//void Scene_battleMap_2::addPlayer(TMXTiledMap* map)
//{
//
//	m_player->setTiledMap(map);//放入地图
//
//	//设置玩家坐标
//	TMXObjectGroup* objGroup = map->getObjectGroup("objects");
//
//	//******************************************************************加载玩家坐标对象
//	ValueMap playerPointMap = objGroup->getObject("player_position");
//	float playerX = playerPointMap.at("x").asFloat();
//	float playerY = playerPointMap.at("y").asFloat();
//
//	m_player->setPosition(Point(playerX, playerY));
//	
//
//	//创建玩家移动控制器
//	Controller_Move* controller_move = Controller_Move::create();
//	controller_move->setiXSpeed(0);
//	controller_move->setiYSpeed(0);
//
//	//添加到场景中
//	this->addChild(controller_move);
//
//	//设置控制器到主角身上
//	//m_player->setController(controller_move);
//	
//	map->addChild(m_player, 3);
//
//
//}
//
//void Scene_battleMap_2::loadUI()
//{
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	//***************************************血条
//	m_hpBar = LoadingBar::create();
//	m_hpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //设置锚点位置
//	m_hpBar->setPosition(Point(20, visibleSize.height - 10));   //设置显示位置,屏幕正中央
//	this->addChild(m_hpBar, 3);  //添加到显示板
//	//这个注释掉后就不会显示了
//
//	//加载进度条资源图片
//	m_hpBar->loadTexture("menu_UI/PlayerHpUI.png"); //进度条
//
//	//设置初始百分比
//	m_hpBar->setPercent(100);
//
//	//设置进度条朝向
//	m_hpBar->setDirection(ui::LoadingBar::Direction::LEFT);
//	m_hpBar->setScale(0.5f);
//
//	//*******************************************************护盾条
//	m_mpBar = LoadingBar::create();
//	m_mpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //设置锚点位置
//	m_mpBar->setPosition(Point(20, visibleSize.height - 40));   //设置显示位置,屏幕正中央
//	this->addChild(m_mpBar, 3);  //添加到显示板
//	//这个注释掉后就不会显示了
//
//	//加载进度条资源图片
//	m_mpBar->loadTexture("menu_UI/PlayerMpUI.png"); //进度条
//
//	//设置初始百分比
//	m_mpBar->setPercent(100);
//
//	//设置进度条朝向
//	m_mpBar->setDirection(ui::LoadingBar::Direction::LEFT);
//	m_mpBar->setScale(0.5f);
//
//	//***********************************************************蓝条
//	m_defendBar = LoadingBar::create();
//	m_defendBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //设置锚点位置
//	m_defendBar->setPosition(Point(20, visibleSize.height - 24));   //设置显示位置,屏幕正中央
//	this->addChild(m_defendBar, 3);  //添加到显示板
//	//这个注释掉后就不会显示了
//
//	//加载进度条资源图片
//	m_defendBar->loadTexture("menu_UI/PlayerDefendeseUI.png"); //进度条
//
//	//设置初始百分比
//	m_defendBar->setPercent(100);
//
//	//设置进度条朝向
//	m_defendBar->setDirection(ui::LoadingBar::Direction::LEFT);
//	m_defendBar->setScale(0.5f);
//}
//
//
