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
	//aimΪ��Ļ���꣬dstPos����Ļ����������ӵ�������������
	Point dstPos = this->getParent()->convertToNodeSpace(aim);

	//�����������
	Point shootVector = dstPos - getPosition();
	//������׼��(����������Ϊ1)
	//Point normalizedVector = ccpNormalize(shootVector);
	//�����ת�Ļ���
	float radians = atan2(shootVector.y, -shootVector.x);
	//������ת���ɽǶ�
	float degree = CC_RADIANS_TO_DEGREES(radians) + 180;




	//������ת��Ҫ��������һ���ٶȣ����������ת�ٶ�Ϊ 2�� (rad/s)
	float rotateSpeed = 20 * M_PI;
	//��ô��ת1��������ʱ��Ϊ
	float rotate_1rad_time = 1 / rotateSpeed;
	//������ת��ʱ��Ϊ
	float rotateDuration = fabs(radians * rotate_1rad_time);


	//���ִ����ת
	m_sprite->runAction(RotateTo::create(rotateDuration, degree));
	//��������������������������������
		//��Ȩ����������ΪCSDN�������������ǡ���ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
		//ԭ�����ӣ�https ://blog.csdn.net/shun_fzll/article/details/34430045
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

