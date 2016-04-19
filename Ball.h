#ifndef _BALL_H__
#define _BALL_H__
#include "cocos2d.h"
#include "BallInfo.h"
#include<string>
using namespace cocos2d;
class Ball : public Sprite {
public:
	Point getcurPoint();								//�����ǰ��λ��
	void setColor(string color);						//������ɫ
	string getColor();									//��õ�ǰ���color


public:
	static Ball* touchedBall;
	bool isChange = false;								//�ж�С���Ƿ�ı�����ɫ
	string color = "";
	bool isShoot = false;								//�ж�С���Ƿ����
	bool isMoved = false;								//
	float time = 1.5;										//�����û��ƶ�С���ʱ��
	float moveBeganX = 0;
	float moveBeganY = 0;
	float moveEndedX = 0;
	float moveEndedY = 0;
};

//���򣬻���������̳�������
class RedBall : public Ball {
public:
	virtual bool init();
	CREATE_FUNC(RedBall);
};

class YellowBall : public Ball {
public:
	virtual bool init();
	CREATE_FUNC(YellowBall);
};
class BlueBall : public Ball {
public:
	virtual bool init();
	CREATE_FUNC(BlueBall);
};
#endif