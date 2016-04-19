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
	void addMonster(float t);						//��ӹ���
	void removeMonster(Node  *pNode);				//�Ƴ�����
	int getScore();									//��÷���
	void updateScore(int score);					//���·���
	void blowupMonster(Monster* pMonsterSprite);	//���޵ı�ըЧ��������û�ж�ͼ���ȷ���
	void update(float t);	
	void control(float t);
	void removeAnimation(string s, Monster *monster);
	void changeCondition(Monster *monster);							//�ı���޵�״̬
	void updateOnce(float t);
	void killMe(Node *pSender);
public:
	float addTime = 3;								//ÿ���������һ�ι���
	float actionTime = 6;							//ִ�ж��������ѵ�ʱ��
	Vector<Monster* > vecMonster;					//��������
	void f_removemyAnimation(Node* pNode);			//����֮���Ƴ�ʱ���ʱ����Ч��
};
#endif
