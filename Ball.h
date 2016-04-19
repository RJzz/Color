#ifndef _BALL_H__
#define _BALL_H__
#include "cocos2d.h"
#include "BallInfo.h"
#include<string>
using namespace cocos2d;
class Ball : public Sprite {
public:
	Point getcurPoint();								//获得球当前的位置
	void setColor(string color);						//设置颜色
	string getColor();									//获得当前球的color


public:
	static Ball* touchedBall;
	bool isChange = false;								//判断小球是否改变了颜色
	string color = "";
	bool isShoot = false;								//判断小球是否射出
	bool isMoved = false;								//
	float time = 1.5;										//计算用户移动小球的时间
	float moveBeganX = 0;
	float moveBeganY = 0;
	float moveEndedX = 0;
	float moveEndedY = 0;
};

//红球，黄球，蓝球类继承自球类
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