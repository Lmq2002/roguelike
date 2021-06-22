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

	//创建精灵


	//*****************************************************将精灵绑定到玩家对象上
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



	//****************************************************为人物添加武器
	//Sprite* m_gun = Sprite::create("Gun/Gun0.png");
	//Weapons* m_weapon = Weapons::create();
	//m_weapon->bindSprite(m_gun);
	//m_weapon->set_position();
	//m_player->addChild(m_weapon, 4);

	//由于addPlayer函数只会调用一次，我们就用update不断更新，带到转向的目的
	//mPlayer->run();
	m_player->scheduleUpdate();

	//mPlayer->run();
	//log("dir %d", direction_x);
	//if (direction_x == 1)
	//{
	//	mPlayer->run();   //让角色跑
	//}
	//if (direction_x == -1)
	//{
	//	mPlayer->run_left();
	//}
	m_player->setTiledMap(map);//放入地图

	//设置玩家坐标
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	//******************************************************************加载玩家坐标对象
	ValueMap playerPointMap = objGroup->getObject("player_position");
	float playerX = playerPointMap.at("x").asFloat();
	float playerY = playerPointMap.at("y").asFloat();
	//log("player_position:%f, %f", m_player->getPosition().x, playerPointMap.at("y"));
	/*********************************************
	*
	此处位置信息获取错误！！！！！！
	player_position:346.874969, 918.749939

	************************************************/


	//mPlayer->setPosition(Point(100, visibleSize.height ));
	m_player->setPosition(Point(playerX, playerY));
	//mPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	//创建玩家移动控制器
	Controller_Move* controller_move = Controller_Move::create();
	controller_move->setiXSpeed(0);
	controller_move->setiYSpeed(0);

	//添加到场景中
	this->addChild(controller_move);

	//设置控制器到主角身上
	m_player->setController(controller_move);
	//m_player->addWeapon();

	//将玩家添加到地图,1代表层数
	map->addChild(m_player, 3);
	//log("player_position:%f, %f", m_weapon->getPosition().x, m_weapon->getPosition().y);
	//addPersistRootNode(this.node);          // 将该节点添加为常驻节点

	auto audio = SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("battleBgm.mp3", true);
	}


	////添加到场景中
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
//	//加载传送门坐标对象
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
	//创建精灵
	Sprite* portalSprite = Sprite::create("portal_1.png");

	//将精灵绑定到玩家对象上
	mPortal = Portal::create();
	mPortal->bindSprite(portalSprite);
	mPortal->bindPlayer(m_player);  //绑定玩家，检测碰撞
	mPortal->act();
	//mPortal->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	mPortal->setScale(1.5f);
	//mPortal->type = 1;


	//设置传送门坐标
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	//加载传送门坐标对象
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
				mMonster->setTiledMap(map);//放入地图

				//怪物创建时一一加入list
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
				mMonster->setTiledMap(map);//放入地图

				//怪物创建时一一加入list
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
			//创建精灵
			Sprite* coinBoxSprite = Sprite::create("coinBoxClose.png");

			//将精灵绑定到玩家对象上
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
	//***************************************血条
	m_hpBar = LoadingBar::create();
	m_hpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //设置锚点位置
	m_hpBar->setPosition(Point(20, visibleSize.height - 10));   //设置显示位置,屏幕正中央
	this->addChild(m_hpBar, 3);  //添加到显示板
	//这个注释掉后就不会显示了

	//加载进度条资源图片
	m_hpBar->loadTexture("menu_UI/PlayerHpUI.png"); //进度条

	//设置初始百分比
	m_hpBar->setPercent(100);

	//设置进度条朝向
	m_hpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_hpBar->setScale(0.5f);

	//*******************************************************护盾条
	m_mpBar = LoadingBar::create();
	m_mpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //设置锚点位置
	m_mpBar->setPosition(Point(20, visibleSize.height - 40));   //设置显示位置,屏幕正中央
	this->addChild(m_mpBar, 3);  //添加到显示板
	//这个注释掉后就不会显示了

	//加载进度条资源图片
	m_mpBar->loadTexture("menu_UI/PlayerMpUI.png"); //进度条

	//设置初始百分比
	m_mpBar->setPercent(100);

	//设置进度条朝向
	m_mpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_mpBar->setScale(0.5f);

	//***********************************************************蓝条
	m_defendBar = LoadingBar::create();
	m_defendBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);  //设置锚点位置
	m_defendBar->setPosition(Point(20, visibleSize.height - 24));   //设置显示位置,屏幕正中央
	this->addChild(m_defendBar, 3);  //添加到显示板
	//这个注释掉后就不会显示了

	//加载进度条资源图片
	m_defendBar->loadTexture("menu_UI/PlayerDefendeseUI.png"); //进度条

	//设置初始百分比
	m_defendBar->setPercent(100);

	//设置进度条朝向
	m_defendBar->setDirection(ui::LoadingBar::Direction::LEFT);
	m_defendBar->setScale(0.5f);
}

void Scene_battleMap::bottomUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建两个精灵
	auto unselected = Sprite::create("gun_buttum.png");
	auto selected = Sprite::create("buttum_redGun.png");
	//auto select = Sprite::create("buttum_redGun.png");


	//创建两个精灵菜单项
	auto unselectedSpriteItem = MenuItemSprite::create(unselected, unselected);
	auto selectedSpriteItem = MenuItemSprite::create(selected, selected);
	//auto selectSpriteItem = MenuItemSprite::create(select, select);

	//创建一个开关菜单项
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
	toggleItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);//锚点设置
	toggleItem->setPosition(Point(visibleSize.width - 40, 40));

	Menu* menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Vec2::ZERO);  //重新设置菜单位置
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

	/*加载Tiled地图，添加到场景中*/

	map = TMXTiledMap::create("battleMap_ice.tmx");

	this->addChild(map);



	addPlayer(map);  //加载骑士
	addMonster(map);

	m_player->getMonsterList(monsterList);   //人物怪物都添加好了之后，就可以将MonsterList传给人物了


	//addmWeapon(map);
	//addWeapon(map);
	addPortal(map);  //加载传送门
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

	/*加载Tiled地图，添加到场景中*/
	TMXTiledMap* map = TMXTiledMap::create("BattleMap_ice_2.tmx");

	this->addChild(map);

	addPlayer(map);  //加载骑士

	addMonster(map);

	m_player->getMonsterList(monsterList);   //人物怪物都添加好了之后，就可以将MonsterList传给人物了

	addPortal(map);  //加载传送门
	mPortal->type = 2;

	addBox(map);

	m_coinLabel = CoinLabel::create();
	m_coinLabel->bindPlayer(m_player);
	addChild(m_coinLabel);
	m_coinLabel->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - 20));

	return true;
}



