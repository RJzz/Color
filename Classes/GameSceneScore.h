#ifndef __GAMESCORE_SCENE_H__
#define __GAMESCORE_SCENE_H__
#include "cocos2d.h"
#include "MonsterLayer.h"
#include "BallLayer.h"
#include "PauseLayer.h"
#include "GameoverLayer.h"
#include "GameData.h"
using namespace cocos2d;
class GameSceneScore : Layer{
public:
	bool init();
	virtual void onEnterTransitionDidFinish();
	void menuCallBack(Ref* pSender);
	CREATE_FUNC(GameSceneScore);
	static Scene * createScene();
	void update(float t);			//��update����С��ʵ��С�������֮�����ײ���
	
public:
	static int scoreS;
protected:
	MonsterLayer *monsterLayer;
	BallLayer *ballLayer;
	PauseLayer *pauseLayer;
	GameoverLayer *gameoverLayer;

};

#endif