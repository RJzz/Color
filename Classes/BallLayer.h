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
	void removeBall(Ball* ball);					//�Ƴ�С��
	static Vector<Ball *> *getBalls();
	void addBall(BallType type);					//���С��
	void mixBall(Ball *ball1, string x);			//�ںϳ��µ���
	void minusTime(float t);					//С����ײ���
	void shootBall(Ball *ball);						//�����ǰС��
	long getCurrentTime();							//��ȡ��ǰʱ�䣬���뼶��
	void update(float t);
	void onTouchEnded(Touch* touch, Event *pEvent);
	void onTouchMoved(Touch *touch, Event *pEvent);
	bool onTouchBegan(Touch *touch, Event *pEvent);
	/*static Vector<Ball* > *allRed;						//��ɫ��������
	static Vector<Ball* > *allBlue;						//��ɫ��������
	static Vector<Ball* > *allYellow;					//��ɫ��������
	static Vector<Ball* > *allPurple;					//��ɫ��������
	static Vector<Ball* > *all;					//��ɫ��������
	static Vector<Ball* > *allOrange;					//��ɫ��������
	static Vector<Ball* > *allBlack;					//��ɫ��������*/
	static Vector<Ball *> *balls;
	
private:
	bool isRe = false;
};

#endif