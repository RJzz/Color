#include "Ball.h"

Ball* Ball::touchedBall = nullptr;
//设置颜色
void Ball::setColor(string color) {
	this->color = color;
}

//获得小球的颜色
string Ball::getColor() {
	return this->color;
}


//获得外包矩形


//重写的红球初始化方法
bool RedBall::init() {
	if (!Sprite::init()) {
		return false;
	}
	// to do

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setColor(RED_BALL);
	this->setTag(BallRed);
	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("redBall.png"));
	this->setPosition(238, 30);
	this->moveBeganX = 235;
	this->moveBeganY = 30;
	return true;

}
//重写的黄球初始化方法
bool YellowBall::init() {
	if (!Sprite::init()) {
		return false;
	}


	// to do



	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setColor(YEIIOW_BALL);
	this->setTag(BallYellow);
	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("yellowBall.png"));
	this->setPosition(134, 55);
	this->moveBeganX = 134;
	this->moveBeganY = 52;
	//this->addEvent();

	return true;
}
//重写的篮球初始化方法
bool BlueBall::init() {
	if (!Sprite::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setColor(BLUE_BALL);
	this->setTag(BallBlue);
	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blueBall.png"));
	this->setPosition(338,55);
	this->moveBeganX = 336;
	this->moveBeganY = 52;

	//this->addEvent();

	return true;
}

