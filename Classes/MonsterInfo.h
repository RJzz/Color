#ifndef __MONSTER_INFO_H__
#define __MONSTER_INFO_H__
#include<string>
using namespace std;
//��������ʱ��ȡ�ķ���ֵ
const int MONSTER_BLUE_SCORE = 1;
const int MONSTER_GREEN_SCORE = 2;
const int MONSTER_RED_SCORE = 1;
const int MONSTER_YELLOW_SCORE = 1;
const int MONSTER_PURPLE_SCORE = 2;
const int MONSTER_BLACK_SCORE = 3;
const int MONSTER_ORANGE_SCORE = 2;
//���޵���ɫ
const string MONSTER_BLUE = "blue";
const string MONSTER_RED = "red";
const string MONSTER_YELLOW = "yellow";
const string MONSTER_PURPLE = "purple";
const string MONSTER_ORANGE = "orange";
const string MONSTER_BLACK = "black";
const string MONSTER_GREEN = "green";
//��ö������������ͬ�ĵ���
enum MonsterType {
	MonsterBlue = 1,
	MonsterRed,
	MonsterYellow,
	MonsterPurple,
	MonsterGreen,
	MonsterOrange,
	MonsterBlack
};
#endif
