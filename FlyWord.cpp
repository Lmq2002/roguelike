#include "FlyWord.h"

FlyWord* FlyWord::create(const string word, const int fontSize, Point begin)
{
	FlyWord* ret = new FlyWord(); //����д����ȫ1Щ 
	if (ret && ret->init(word, fontSize, begin))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);//��ȫɾ�� 
	return nullptr;
}

bool FlyWord::init(const string word, const int fontSize, Point pos_begin)
{
	if (!Node::init())
	{ return false; } //��ʼ�� 
	//pos_begin = begin; 
	m_words = Label::createWithTTF(word,"arial",fontSize); //����ɫ�� 
	Color3B RGB; 
	RGB.r=255; 
	RGB.g=0; 
	RGB.b=0; 
	m_words->setColor(RGB); 
	this->addChild(m_words); 
	this->setPosition(pos_begin); //��ʼ����ɺ�Ϳ�ʼƮ���� 
	Flying(); 
	return true;
}

void FlyWord::Flying()
{
	MoveBy* moveact = MoveBy::create(0.5f, Point(0, 70));//0.5�������ƶ�70 
														 //�����ص����������ַ������ 
	//CallFunc* callFunc=CallFunc::create(this,callfunc_selector(FlyWord::Flyend)); //������������
	//ActionInterval* act=Sequence::create(moveact,NULL,NULL); //
	setVisible(true); 
	this->runAction(moveact);
	Flyend();
}

void FlyWord::Flyend()
{
	this->setVisible(false);
	this->setPosition(pos_begin);
}
