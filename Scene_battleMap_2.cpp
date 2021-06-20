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
//	/*����Tiled��ͼ����ӵ�������*/
//	TMXTiledMap* map = TMXTiledMap::create("BattleMap_ice_2.tmx");
//	
//
//	this->addChild(map);
//
//
//	addPlayer(map);  //������ʿ
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
//	m_player->setTiledMap(map);//�����ͼ
//
//	//�����������
//	TMXObjectGroup* objGroup = map->getObjectGroup("objects");
//
//	//******************************************************************��������������
//	ValueMap playerPointMap = objGroup->getObject("player_position");
//	float playerX = playerPointMap.at("x").asFloat();
//	float playerY = playerPointMap.at("y").asFloat();
//
//	m_player->setPosition(Point(playerX, playerY));
//	
//
//	//��������ƶ�������
//	Controller_Move* controller_move = Controller_Move::create();
//	controller_move->setiXSpeed(0);
//	controller_move->setiYSpeed(0);
//
//	//��ӵ�������
//	this->addChild(controller_move);
//
//	//���ÿ���������������
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
//	//***************************************Ѫ��
//	m_hpBar = LoadingBar::create();
//	m_hpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //����ê��λ��
//	m_hpBar->setPosition(Point(20, visibleSize.height - 10));   //������ʾλ��,��Ļ������
//	this->addChild(m_hpBar, 3);  //��ӵ���ʾ��
//	//���ע�͵���Ͳ�����ʾ��
//
//	//���ؽ�������ԴͼƬ
//	m_hpBar->loadTexture("menu_UI/PlayerHpUI.png"); //������
//
//	//���ó�ʼ�ٷֱ�
//	m_hpBar->setPercent(100);
//
//	//���ý���������
//	m_hpBar->setDirection(ui::LoadingBar::Direction::LEFT);
//	m_hpBar->setScale(0.5f);
//
//	//*******************************************************������
//	m_mpBar = LoadingBar::create();
//	m_mpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //����ê��λ��
//	m_mpBar->setPosition(Point(20, visibleSize.height - 40));   //������ʾλ��,��Ļ������
//	this->addChild(m_mpBar, 3);  //��ӵ���ʾ��
//	//���ע�͵���Ͳ�����ʾ��
//
//	//���ؽ�������ԴͼƬ
//	m_mpBar->loadTexture("menu_UI/PlayerMpUI.png"); //������
//
//	//���ó�ʼ�ٷֱ�
//	m_mpBar->setPercent(100);
//
//	//���ý���������
//	m_mpBar->setDirection(ui::LoadingBar::Direction::LEFT);
//	m_mpBar->setScale(0.5f);
//
//	//***********************************************************����
//	m_defendBar = LoadingBar::create();
//	m_defendBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //����ê��λ��
//	m_defendBar->setPosition(Point(20, visibleSize.height - 24));   //������ʾλ��,��Ļ������
//	this->addChild(m_defendBar, 3);  //��ӵ���ʾ��
//	//���ע�͵���Ͳ�����ʾ��
//
//	//���ؽ�������ԴͼƬ
//	m_defendBar->loadTexture("menu_UI/PlayerDefendeseUI.png"); //������
//
//	//���ó�ʼ�ٷֱ�
//	m_defendBar->setPercent(100);
//
//	//���ý���������
//	m_defendBar->setDirection(ui::LoadingBar::Direction::LEFT);
//	m_defendBar->setScale(0.5f);
//}
//
//
