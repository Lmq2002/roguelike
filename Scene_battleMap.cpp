#include "Scene_battleMap.h"
#include "SafeMap.h"
#include "GameBeginScene.h"

extern int direction_x, direction_y;

//Scene* Scene_battleMap::createScene()
//{
//	//Size winSize = Director::getInstance()->getWinSize();
//	auto scene = Scene::create();
//	auto layer = Scene_battleMap::create();
//
//
//	scene->addChild(layer);
//
//	return scene;
//}

void Scene_battleMap::update(float dt)
{
	//auto weapon_move = MoveBy::create(0.0f, Point(10, 0));
	//m_weapon->runAction(weapon_move);

	m_defendBar->setPercent(m_player->getDefence() / 10.0f * 100);
	m_hpBar->setPercent(m_player->getiHP() / 10.0f * 100);
	m_mpBar->setPercent(m_player->getiMP() / 200.0f * 100);
	//log("Hp: %d", m_player->getiHP());


	if (!m_player->isAlive())
	{
		m_player->setVisible(false);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("death.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("menu.mp3");
		Director::getInstance()->replaceScene(SafeMap::createScene());
	}
}

void Scene_battleMap::addPlayer(TMXTiledMap* map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//��������


	//*****************************************************������󶨵���Ҷ�����
	if (m_player == NULL)
	{
		Sprite* playerSprite = Sprite::create("boy_run1.png");

		m_player = Player::create();
		m_player->bindSprite(playerSprite);
	}


	//RecordData::bindPlayer(m_player);

	m_player->setContentSize(Size(40, 40));
	//m_player->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);

	m_player->addWeapon();
	m_player->addKnife();



	//****************************************************Ϊ�����������
	//Sprite* m_gun = Sprite::create("Gun/Gun0.png");
	//Weapons* m_weapon = Weapons::create();
	//m_weapon->bindSprite(m_gun);
	//m_weapon->set_position();
	//m_player->addChild(m_weapon, 4);

	//����addPlayer����ֻ�����һ�Σ����Ǿ���update���ϸ��£�����ת���Ŀ��
	//mPlayer->run();
	m_player->scheduleUpdate();

	//mPlayer->run();
	//log("dir %d", direction_x);
	//if (direction_x == 1)
	//{
	//	mPlayer->run();   //�ý�ɫ��
	//}
	//if (direction_x == -1)
	//{
	//	mPlayer->run_left();
	//}
	m_player->setTiledMap(map);//�����ͼ

	//�����������
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	//******************************************************************��������������
	ValueMap playerPointMap = objGroup->getObject("player_position");
	float playerX = playerPointMap.at("x").asFloat();
	float playerY = playerPointMap.at("y").asFloat();
	//log("player_position:%f, %f", m_player->getPosition().x, playerPointMap.at("y"));
	/*********************************************
	*
	�˴�λ����Ϣ��ȡ���󣡣���������
	player_position:346.874969, 918.749939

	************************************************/


	//mPlayer->setPosition(Point(100, visibleSize.height ));
	m_player->setPosition(Point(playerX, playerY));
	//mPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	//��������ƶ�������
	Controller_Move* controller_move = Controller_Move::create();
	controller_move->setiXSpeed(0);
	controller_move->setiYSpeed(0);

	//��ӵ�������
	this->addChild(controller_move);

	//���ÿ���������������
	m_player->setController(controller_move);
	//m_player->addWeapon();

	//�������ӵ���ͼ,1�������
	map->addChild(m_player, 3);
	//log("player_position:%f, %f", m_weapon->getPosition().x, m_weapon->getPosition().y);
	//addPersistRootNode(this.node);          // ���ýڵ����Ϊ��פ�ڵ�

	auto audio = SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("battleBgm.mp3", true);
	}


	////��ӵ�������
	//this->addChild(controller_move);
}

//void Scene_battleMap::addWeapon(TMXTiledMap* map)
//{
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//
//	Sprite* m_gun = Sprite::create("Gun/Gun0.png");
//	//m_weapon->set_position();
//	TMXObjectGroup* objGroup = map->getObjectGroup("objects");
//
//	//���ش������������
//	ValueMap weaponMap = objGroup->getObject("weapon");
//	float weaponX = weaponMap.at("x").asFloat();
//	float weaponY = weaponMap.at("y").asFloat();
//
//	Point beg_pos = Point(weaponX, weaponY);
//
//	Weapons* m_weapon = NULL;
//	m_weapon = Weapons::create();
//	m_weapon->bindPlayer(m_player);
//	m_weapon->bindSprite(m_gun);
//
//	//m_weapon->setPosition(beg_pos);
//	m_weapon->set_position();
//
//	//m_weapon->setDirection(m_weapon->getPosition());
//
//	map->addChild(m_weapon, 4);
//	//m_player->addChild(m_weapon, 4);
//
//
//}

void Scene_battleMap::addPortal(TMXTiledMap* map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��������
	Sprite* portalSprite = Sprite::create("portal_1.png");

	//������󶨵���Ҷ�����
	mPortal = Portal::create();
	mPortal->bindSprite(portalSprite);
	mPortal->bindPlayer(m_player);  //����ң������ײ
	mPortal->act();
	//mPortal->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	mPortal->setScale(1.5f);
	//mPortal->type = 1;


	//���ô���������
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	//���ش������������
	ValueMap portalMap = objGroup->getObject("portal");
	float portalX = portalMap.at("x").asFloat();
	float portalY = portalMap.at("y").asFloat();

	//mPortal->setTiledMap(map);

	mPortal->setPosition(Point(portalX, portalY));

	map->addChild(mPortal, 0);

}

void Scene_battleMap::addMonster(TMXTiledMap* map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	TMXObjectGroup* mstGroup = map->getObjectGroup("Monsters");

	ValueVector mstArray = mstGroup->getObjects();

	//float x, y, w, h;

	for each (Value mstPointMap in mstArray)
	{
		ValueMap mstPoint = mstPointMap.asValueMap();
		float posX = mstPoint.at("x").asFloat();
		float posY = mstPoint.at("y").asFloat();

		
		Point monsterPoint = Point(posX, posY);
	/*	posY -= this->getTileSize().height;
		Point tileXY = this->positionToTileCoord(ccp(posX, posY));
		std::string name = objPoint.at("name").asString();
		std::string type = objPoint.at("type").asString();*/

		std::string name = mstPoint.at("name").asString();
		std::string type = mstPoint.at("type").asString();

		if (name == "monster")
		{
			Monster* mMonster = NULL;
			if (type == "striker")
			{
				mMonster = MonsterStriker::create();
				mMonster->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

				mMonster->bindPlayer(m_player);
				mMonster->bindSprite(Sprite::create("mst_scorer2.png"));
				//if (m_player->getPBullet() != NULL)
					//mMonster->bindBullet(m_player->getPBullet());

	
				//Point mstPoint;
				mMonster->setPosition(monsterPoint);


				map->addChild(mMonster, 3);
				mMonster->setTiledMap(map);//�����ͼ

				//���ﴴ��ʱһһ����list
				if (mMonster->isAlive())
					monsterList.pushBack(mMonster);
			}
			if (type == "pig")
			{
				mMonster = MonsterPig::create();
				mMonster->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				mMonster->setScale(0.8f);

				mMonster->bindPlayer(m_player);
				mMonster->bindSprite(Sprite::create("wild_pig.png"));
				
				mMonster->setPosition(monsterPoint);

				map->addChild(mMonster, 3);
				mMonster->setTiledMap(map);//�����ͼ

				//���ﴴ��ʱһһ����list
				if (mMonster->isAlive())
					monsterList.pushBack(mMonster);
			}

		}
	}

	//m_player->getMonsterList(monsterList);

}

void Scene_battleMap::addBox(TMXTiledMap* map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	ValueVector objArray = objGroup->getObjects();

	//float x, y, w, h;

	for each (Value objPointMap in objArray)
	{
		ValueMap objPoint = objPointMap.asValueMap();
		float posX = objPoint.at("x").asFloat();
		float posY = objPoint.at("y").asFloat();


		Point monsterPoint = Point(posX, posY);
		/*	posY -= this->getTileSize().height;
			Point tileXY = this->positionToTileCoord(ccp(posX, posY));
			std::string name = objPoint.at("name").asString();
			std::string type = objPoint.at("type").asString();*/

		std::string name = objPoint.at("name").asString();
		//std::string type = objPoint.at("type").asString();

		if (name == "box")
		{
			//��������
			Sprite* coinBoxSprite = Sprite::create("coinBoxClose.png");

			//������󶨵���Ҷ�����
			CoinBox* mCoinBox = CoinBox::create();
			mCoinBox->bindSprite(coinBoxSprite);
			

			mCoinBox->setPosition(monsterPoint);
			mCoinBox->showBox();
			mCoinBox->bindPlayer(m_player);
			//mCoinBox->openAni();

			map->addChild(mCoinBox, 4);


		}
	}


	
}



void Scene_battleMap::loadUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//***************************************Ѫ��
	m_hpBar = LoadingBar::create();
	m_hpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //����ê��λ��
	m_hpBar->setPosition(Point(20, visibleSize.height - 10));   //������ʾλ��,��Ļ������
	this->addChild(m_hpBar, 3);  //��ӵ���ʾ��
	//���ע�͵���Ͳ�����ʾ��

	//���ؽ�������ԴͼƬ
	m_hpBar->loadTexture("menu_UI/PlayerHpUI.png"); //������

	//���ó�ʼ�ٷֱ�
	m_hpBar->setPercent(100);

	//���ý���������
	m_hpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_hpBar->setScale(0.5f);

	//*******************************************************������
	m_mpBar = LoadingBar::create();
	m_mpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //����ê��λ��
	m_mpBar->setPosition(Point(20, visibleSize.height - 40));   //������ʾλ��,��Ļ������
	this->addChild(m_mpBar, 3);  //��ӵ���ʾ��
	//���ע�͵���Ͳ�����ʾ��

	//���ؽ�������ԴͼƬ
	m_mpBar->loadTexture("menu_UI/PlayerMpUI.png"); //������

	//���ó�ʼ�ٷֱ�
	m_mpBar->setPercent(100);

	//���ý���������
	m_mpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_mpBar->setScale(0.5f);

	//***********************************************************����
	m_defendBar = LoadingBar::create();
	m_defendBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //����ê��λ��
	m_defendBar->setPosition(Point(20, visibleSize.height - 24));   //������ʾλ��,��Ļ������
	this->addChild(m_defendBar, 3);  //��ӵ���ʾ��
	//���ע�͵���Ͳ�����ʾ��

	//���ؽ�������ԴͼƬ
	m_defendBar->loadTexture("menu_UI/PlayerDefendeseUI.png"); //������

	//���ó�ʼ�ٷֱ�
	m_defendBar->setPercent(100);

	//���ý���������
	m_defendBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_defendBar->setScale(0.5f);
}

void Scene_battleMap::bottomUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//������������
	auto unselected = Sprite::create("gun_buttum.png");
	auto selected = Sprite::create("buttum_redGun.png");
	//auto select = Sprite::create("buttum_redGun.png");


	//������������˵���
	auto unselectedSpriteItem = MenuItemSprite::create(unselected, unselected);
	auto selectedSpriteItem = MenuItemSprite::create(selected, selected);
	//auto selectSpriteItem = MenuItemSprite::create(select, select);

	//����һ�����ز˵���
	auto toggleItem = MenuItemToggle::createWithCallback([&](Ref* ref) {
		auto item = dynamic_cast<MenuItemToggle*>(ref);
		if (item)
		{
			if (item->getSelectedIndex() == 0)
			{
				m_player->setBulletType("Gun");
			}
			else if (item->getSelectedIndex() == 1)
			{
				m_player->setBulletType("redGun");
			}

		}
		}, unselectedSpriteItem, selectedSpriteItem, NULL);
	toggleItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);//ê������
	toggleItem->setPosition(Point(visibleSize.width - 40, 40));

	Menu* menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Vec2::ZERO);  //�������ò˵�λ��
	this->addChild(menu,5);
}

void Scene_battleMap::registeKeyBoardEvent()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_F) {
			if (mPortal->isCollisionWithPlayer()) {

				for (auto monster : monsterList) {
					if (monster->isAlive()) {
						return;
					}
				}
			}
			if (mPortal->type == 1)
				Director::getInstance()->replaceScene(Scene_battleMap_2::createScene());
			if (mPortal->type == 2) {
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				Director::getInstance()->replaceScene(GameBeginScene::createScene());
			}
		}

	};
	listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_F) {
			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


//**************************************************************




Scene* Scene_battleMap_1::createScene()
{
	auto scene = Scene::create();
	auto layer = Scene_battleMap_1::create();


	scene->addChild(layer);

	return scene;
}

bool Scene_battleMap_1::init()
{
	//registeTouchEvent();
	//map_name = "battleMap_ice.tmx"; 
	registeKeyBoardEvent();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (!Layer::init())return false;

	Sprite* bg_UI = Sprite::create("menu_UI/background_UI.png");
	bg_UI->setPosition(Point(0, visibleSize.height));
	bg_UI->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	bg_UI->setScale(0.5f);
	this->addChild(bg_UI, 2);

	//addMap();

	loadUI();
	bottomUI();


	this->scheduleUpdate();

	/*����Tiled��ͼ����ӵ�������*/

	map = TMXTiledMap::create("battleMap_ice.tmx");

	this->addChild(map);



	addPlayer(map);  //������ʿ
	addMonster(map);

	m_player->getMonsterList(monsterList);   //������ﶼ��Ӻ���֮�󣬾Ϳ��Խ�MonsterList����������


	//addmWeapon(map);
	//addWeapon(map);
	addPortal(map);  //���ش�����
	mPortal->type = 1;
	

	addBox(map);
	
	m_coinLabel = CoinLabel::create();
	m_coinLabel->bindPlayer(m_player);
	addChild(m_coinLabel);
	m_coinLabel->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - 20));


	return true;
}





//*******************************************
Scene* Scene_battleMap_2::createScene()
{
	auto scene = Scene::create();
	auto layer = Scene_battleMap_2::create();


	scene->addChild(layer);

	return scene;
}


bool Scene_battleMap_2::init()
{
	registeKeyBoardEvent();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (!Layer::init())return false;

	Sprite* bg_UI = Sprite::create("menu_UI/background_UI.png");
	bg_UI->setPosition(Point(0, visibleSize.height));
	bg_UI->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	bg_UI->setScale(0.5f);
	this->addChild(bg_UI, 2);

	loadUI();
	bottomUI();
	

	this->scheduleUpdate();

	/*����Tiled��ͼ����ӵ�������*/
	TMXTiledMap* map = TMXTiledMap::create("BattleMap_ice_2.tmx");

	this->addChild(map);

	addPlayer(map);  //������ʿ

	addMonster(map);

	m_player->getMonsterList(monsterList);   //������ﶼ��Ӻ���֮�󣬾Ϳ��Խ�MonsterList����������

	addPortal(map);  //���ش�����
	mPortal->type = 2;

	addBox(map);

	m_coinLabel = CoinLabel::create();
	m_coinLabel->bindPlayer(m_player);
	addChild(m_coinLabel);
	m_coinLabel->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - 20));

	return true;
}



