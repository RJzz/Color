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
	void cleanMonster();				//�������
	void beingStrong();					//�޵�״̬
	void iceMonster();					//��������
	void getLife();						//�������ֵ
	void doubleScore();					//��һ��ʱ���ڻ��˫������
	void control(float t);
	void iceAction(Monster *monster, string s, int number);
	void killMe(Node *pSender);
	void boomControl(float t);
public:
	static int scoreTool;
protected:
	int controlDouble = 0;				//����˫����ʱ��
	int controlStrong = 0;				//�����޵е�ʱ��

	Vector<Tools* > clean;				//�������
	Vector<Tools *> ice;				//��������
	MonsterLayer *monsterLayer;
	BallLayer *ballLayer;
	PauseLayer *pauseLayer;
	ToolsLayer *toolsLayer;
	GameoverLayer *gameoverLayer;

};
#endif