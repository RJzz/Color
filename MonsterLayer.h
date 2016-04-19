#ifndef __MONSTER_LAYER_H__
#define __MONSTER_LAYER_H__
#include<string>
#include "cocos2d.h"
#include "Monster.h"
#include "MonsterInfo.h"

USING_NS_CC;
using namespace cocos2d;
class MonsterLayer : public Layer {
public:
	bool init();
	CREATE_FUNC(MonsterLayer);
public:
	void addMonster(float t);						//添加怪兽
	void removeMonster(Node  *pNode);				//移除怪兽
	int getScore();									//获得分数
	void updateScore(int score);					//更新分数
	void blowupMonster(Monster* pMonsterSprite);	//怪兽的爆炸效果，现在没有动图，先放着
	void update(float t);	
	void control(float t);
	void removeAnimation(string s, Monster *monster);
	void changeCondition(Monster *monster);							//改变怪兽的状态
	void updateOnce(float t);
	void killMe(Node *pSender);
public:
	float addTime = 3;								//每隔几秒添加一次怪兽
	float actionTime = 6;							//执行动作所花费的时间
	Vector<Monster* > vecMonster;					//怪兽容器
	void f_removemyAnimation(Node* pNode);			//碰线之后，移除时候的时动画效果
};
#endif
