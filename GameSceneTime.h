#ifndef __GAMESCENE_TIME_H__
#define __GAMESCENE_TIME_H__
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "PauseLayer.h"
#include "MonsterLayer.h"
#include "BallLayer.h"
#include "GameData.h"
#include "GameoverLayer.h"
using namespace cocos2d;
class GameSceneTime : public Layer {
public :
	bool init();
	CREATE_FUNC(GameSceneTime);
	static Scene * createScene();
	void menuCallBack(Ref* r);
	virtual void onEnterTransitionDidFinish();
	void update(float t);			//��update����С��ʵ��С�������֮�����ײ���
	void timeMinus(float t);		//ʱ�䵹��ʱ����
public:
	static int scoreT;					//����
protected:
	BallLayer* ballLayer;				//���
	MonsterLayer* monsterLayer;			//���޲�
	PauseLayer* pauseLayer;				//��ͣ��
	GameoverLayer* gameoverLayer;		//��Ϸ������
	int time;
};
#endif