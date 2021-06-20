#pragma once
#ifndef _FlyWord_H_
#define _FlyWord_H_
#include "cocos2d.h" 
#include "cocos-ext.h" 
#include "iostream"
USING_NS_CC; 
USING_NS_CC_EXT; 
using namespace std;

class FlyWord :public Node{
public:
	static FlyWord* create(const string word, const int fontSize, Point begin);
	bool init(const string word, const int fontSize, Point begin);

	void Flying();//文字从下到上飞舞

	void Flyend();//飞舞结束后删除文字

private:
	int fontSize;//文字大小
	Point pos_begin;//文字出生地址

	Label* m_words;//字体类型

	//string str = asString(fontSize);
};


#endif