#ifndef __SETTING_LAYER_H_
#define __SETTING_LAYER_H_
#include "cocos2d.h"
#include "AboutLayer.h"
using namespace cocos2d;
class SettingLayer : public Layer{
public:
	bool init();
	void menuCallBack(Ref* pSender);
	CREATE_FUNC(SettingLayer);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
public:
	AboutLayer* aboutLayer;
	MenuItemImage* on1;
	MenuItemImage* off1;


	MenuItemImage* on2;
	MenuItemImage* off2;


};
#endif