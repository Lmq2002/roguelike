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

	void Flying();//���ִ��µ��Ϸ���

	void Flyend();//���������ɾ������

private:
	int fontSize;//���ִ�С
	Point pos_begin;//���ֳ�����ַ

	Label* m_words;//��������

	//string str = asString(fontSize);
};


#endif