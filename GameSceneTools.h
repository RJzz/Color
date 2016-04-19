#ifndef __GAMESCENE_TOOLS_H__
#define __GAMESCENE_TOOLS_H__
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "BallLayer.h"
#include "MonsterLayer.h"
#include "ToolsLayer.h"
#include "PauseLayer.h"
#include "GameoverLayer.h"
#include "GameData.h"
using namespace cocos2d;
class GameSceneTools : public Layer {
public:
	bool init();
	CREATE_FUNC(GameSceneTools);
	static Scene * createScene();
	void update(float t);
	virtual void onEnterTransitionDidFinish();
	void menuCallBack(Ref* pSender);
	void cleanMonster();				//清除怪兽
	void beingStrong();					//无敌状态
	void iceMonster();					//冰冻怪兽
	void getLife();						//获得生命值
	void doubleScore();					//在一段时间内获得双倍分数
	void control(float t);
	void iceAction(Monster *monster, string s, int number);
	void killMe(Node *pSender);
	void boomControl(float t);
public:
	static int scoreTool;
protected:
	int controlDouble = 0;				//控制双倍的时间
	int controlStrong = 0;				//控制无敌的时间

	Vector<Tools* > clean;				//清楚道具
	Vector<Tools *> ice;				//冰冻道具
	MonsterLayer *monsterLayer;
	BallLayer *ballLayer;
	PauseLayer *pauseLayer;
	ToolsLayer *toolsLayer;
	GameoverLayer *gameoverLayer;

};
#endif