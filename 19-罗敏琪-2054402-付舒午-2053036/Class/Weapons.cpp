#include "Weapons.h"

Weapons::Weapons()
{
	ifLaunch = false;
	Type = "Gun";
}

Weapons::~Weapons()
{

}

bool Weapons::init()
{
	//registe_listener_getDirection();
	
	return true;
}

void Weapons::update(float dt)
{

}


bool Weapons::isAttack()
{
	return ifLaunch;
}

void Weapons::setDirection(Point aim)
{
	//aim为屏幕坐标，dstPos是屏幕坐标相对于子弹管理器的坐标
	Point dstPos = this->getParent()->convertToNodeSpace(aim);

	//射击方向向量
	Point shootVector = dstPos - getPosition();
	//向量标准化(即向量长度为1)
	//Point normalizedVector = ccpNormalize(shootVector);
	//算出旋转的弧度
	float radians = atan2(shootVector.y, -shootVector.x);
	//将弧度转换成角度
	float degree = CC_RADIANS_TO_DEGREES(radians) + 180;




	//匀速旋转需要我们设置一下速度，这里假设旋转速度为 2π (rad/s)
	float rotateSpeed = 20 * M_PI;
	//那么旋转1弧度所用时间为
	float rotate_1rad_time = 1 / rotateSpeed;
	//所以旋转的时长为
	float rotateDuration = fabs(radians * rotate_1rad_time);


	//最后执行旋转
	m_sprite->runAction(RotateTo::create(rotateDuration, degree));
	//————————————————
		//版权声明：本文为CSDN博主「风中老狼」的原创文章，遵循CC 4.0 BY - SA版权协议，转载请附上原文出处链接及本声明。
		//原文链接：https ://blog.csdn.net/shun_fzll/article/details/34430045
}

void Weapons::fireAnimation()
{

}

void Weapons::setType(string type)
{
	Type = type;
}

string Weapons::getType()
{
	return Type;
}

//void Weapons::bindPlayer(Player* player)
//{
//	m_player = player;
//}

//void Weapons::registe_listener_getDirection()
//{
//	auto listener_getDirection = EventListenerTouchOneByOne::create();
//
//	// trigger when you push down
//	listener_getDirection->onTouchBegan = [this](Touch* touch, Event* event) {
//		// your code
//		target_pos = touch->getLocation();
//		log("touch!!!");
//		//set_position();
//		//setDirection(getPosition());
//		//ifLaunch = true;
//		return true; // if you are consuming it
//	};
//
//	// trigger when moving touch
//	listener_getDirection->onTouchMoved = [](Touch* touch, Event* event) {
//		// your code
//	};
//
//	// trigger when you let up
//	listener_getDirection->onTouchEnded = [=](Touch* touch, Event* event) {
//		// your code
//	};
//
//	// Add listener
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_getDirection, this);
//}

