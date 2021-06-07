#pragma once
#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "cocos2d.h"
#define MPMAX 6
#define ACMAX 7
#define HPMAX 180
#define SPEED 1
using namespace cocos2d;

class Knight:
	public cocos2d::Node
{
	virtual int getMP(int MP);
	virtual int getHP(int HP);
	virtual void setMP(int MP);
	virtual void setHP(int HP);
	virtual void setSpeed(int speed);
//	virtual bool create() = 0;
//	virtual Sprite* create();


};

class Paladin :
	public Knight
{
public:
	Sprite* myPaladin;
	SpriteFrame* normalLeft;
	SpriteFrame* runLeft;
	SpriteFrame* normalRight;
	SpriteFrame* runRight;
	Sprite* dieRight;
	Sprite* dieLeft;

	enum Direction {
		Left,
		Right
	};


	//��ʼ��ͼ����
	Paladin();
	~Paladin();

	bool getIsLive();
	void setDead();

	//���������
	void onEnter();
	void onExit();

	//����ָ��
	static Paladin* paladinInstance;
	//�Ѷ���ָ�봫��ȥ�����Ѷ��������������
	static Paladin* getPaladinInstance();
	//��Ψһһ�����󣬸�һ���ڴ档
	static Paladin* create();

	//���ͼ�����ﵽ��������Ŀ�ģ�����ڳ�������ʵ�ֺ���
	void dieAnimation();
	//�����ͼ�߽��ʱ�����Ҫ�õ�moveby?
	void runAnimation();

	//��������֮��
	void hit(int attack);
	//��ײ������ж�
	bool isHit();
	bool isListenerAllowed();

	void bindEnermy(Sprite* enermy);

	//���ǳ�������
	void born();
	//��Ϸ���¿�ʼ����������Ϣ
	void reset();
	

private:
	bool init();
	bool isLive;
	int MP;
	int HP;
	int AC;
	int speed;
	int score;
	Sprite* enermy;
	Direction direction;
	//δ֪
	cocos2d::Point position;
	//���ǿ�ߣ����������ײ
	Size size;
};

class Berserker :
	public Knight
{
	int MP;
	int HP;
	int speed;
	std::string fileName;
	virtual bool init();
//	Sprite* create();
};

#endif
