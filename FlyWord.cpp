#include "FlyWord.h"

FlyWord* FlyWord::create(const string word, const int fontSize, Point begin)
{
	FlyWord* ret = new FlyWord(); //这样写更安全1些 
	if (ret && ret->init(word, fontSize, begin))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);//安全删除 
	return nullptr;
}

bool FlyWord::init(const string word, const int fontSize, Point pos_begin)
{
	if (!Node::init())
	{ return false; } //初始化 
	//pos_begin = begin; 
	m_words = Label::createWithTTF(word,"arial",fontSize); //设置色彩 
	Color3B RGB; 
	RGB.r=255; 
	RGB.g=0; 
	RGB.b=0; 
	m_words->setColor(RGB); 
	this->addChild(m_words); 
	this->setPosition(pos_begin); //初始化完成后就开始飘字了 
	Flying(); 
	return true;
}

void FlyWord::Flying()
{
	MoveBy* moveact = MoveBy::create(0.5f, Point(0, 70));//0.5秒向上移动70 
														 //创建回调动作，文字飞舞完后 
	//CallFunc* callFunc=CallFunc::create(this,callfunc_selector(FlyWord::Flyend)); //创建连续动作
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
