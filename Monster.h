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
	void setMonsterByType(MonsterType moType);		//���ù��޾��������
	Rect getBoundingBox();							//��ȡ�����Ĺ��޾���ľ��α߽�
	Sprite* getSprite();							//��ȡ�����Ĺ��޾���								
	Point getcurPoint();							//��ȡ�������ڵ�λ��
	void setColor(string c);						//���ù��޵���ɫ
	void setScore(int i);							//���ù��޵ķ���
	string getColor();								//���ع��޵���ɫ
	int getScore();									//���ع��޵ķ���
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