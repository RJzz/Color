#ifndef __BALL_LAYER_H__
#define __BALL_LAYER_H__
#include "cocos2d.h"
#include "Ball.h"
USING_NS_CC;
using namespace cocos2d;
class BallLayer : public Layer {
public:
	bool init();
	CREATE_FUNC(BallLayer);
public:
	void removeBall(Ball* ball);					//移除小球
	static Vector<Ball *> *getBalls();
	void addBall(BallType type);					//添加小球
	void mixBall(Ball *ball1, string x);			//融合出新的球
	void minusTime(float t);					//小球碰撞检测
	void shootBall(Ball *ball);						//射出当前小球
	long getCurrentTime();							//获取当前时间，毫秒级别
	void update(float t);
	void onTouchEnded(Touch* touch, Event *pEvent);
	void onTouchMoved(Touch *touch, Event *pEvent);
	bool onTouchBegan(Touch *touch, Event *pEvent);
	/*static Vector<Ball* > *allRed;						//红色怪兽容器
	static Vector<Ball* > *allBlue;						//蓝色怪兽容器
	static Vector<Ball* > *allYellow;					//黄色怪兽容器
	static Vector<Ball* > *allPurple;					//紫色怪兽容器
	static Vector<Ball* > *all;					//绿色怪兽容器
	static Vector<Ball* > *allOrange;					//橙色怪兽容器
	static Vector<Ball* > *allBlack;					//黑色怪兽容器*/
	static Vector<Ball *> *balls;
	
private:
	bool isRe = false;
};

#endif