#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "SettingLayer.h"
#include "HistoryLayer.h"
class HelloWorld : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void update(float t);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void changeReady(float t);
public:
	bool readyEnd = false;
	static int life;							//生命
	static bool isDouble;				//是否双倍分数
	static bool unStoppable;			//无敌！无法阻挡
	static int mode;
	SettingLayer* settingLayer;
	HistoryLayer* historyLayer;
};

#endif // __HELLOWORLD_SCENE_H__
