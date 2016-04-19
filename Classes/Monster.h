#ifndef __MONSTER_H__
#define __MONSTER_H__
#include<string>
#include "cocos2d.h"
#include "MonsterInfo.h"
USING_NS_CC;
using namespace cocos2d;
class Monster : public Node {
public:

	CREATE_FUNC(Monster);
	void setMonsterByType(MonsterType moType);		//设置怪兽精灵的类型
	Rect getBoundingBox();							//获取创建的怪兽精灵的矩形边界
	Sprite* getSprite();							//获取创建的怪兽精灵								
	Point getcurPoint();							//获取怪兽现在的位置
	void setColor(string c);						//设置怪兽的颜色
	void setScore(int i);							//设置怪兽的分数
	string getColor();								//返回怪兽的颜色
	int getScore();									//返回怪兽的分数
	void moveAnimation(MonsterType moType);
	Sprite *pMonsterSprite;
	void walk(string s, int pictureN);
	void resumeWalk(float t);
	bool frozen = false;
	bool hit = false;
private:
	string color;
	int score;
	
};
#endif