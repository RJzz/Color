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
	void update(float t);			//在update中有小球实现小球与怪兽之间的碰撞检测
	void timeMinus(float t);		//时间倒计时函数
public:
	static int scoreT;					//分数
protected:
	BallLayer* ballLayer;				//球层
	MonsterLayer* monsterLayer;			//怪兽层
	PauseLayer* pauseLayer;				//暂停层
	GameoverLayer* gameoverLayer;		//游戏结束层
	int time;
};
#endif