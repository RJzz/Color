#ifndef __BALLINFO_H__
#define __BALLINFO_H__
#include<string>
using namespace std;
//不同球的颜色
const string BLUE_BALL = "blue";
const string RED_BALL = "red";
const string YEIIOW_BALL = "yellow";
const string PURPLE_BALL = "purple";
const string ORANGE_BALL = "orange";
const string GREEN_BALL = "green";
const string BLACK_BALL = "black";

//用枚举类型来区别不同的小球
enum BallType{
	BallRed = 1,
	BallYellow,
	BallBlue,
	BallOrange,
	BallPurple,
	BallGreen,
	BallBlack
};

#endif