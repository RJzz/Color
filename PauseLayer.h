#ifndef _PAUSE_LAYER_H_
#define _PAUSE_LAYER_H_
#include "cocos2d.h"
#include "SettingLayer.h"
using namespace cocos2d;
class PauseLayer : public Layer {
public:
	bool init();
	CREATE_FUNC(PauseLayer);
	void menuCallBack(Ref* pSender);
public:
	SettingLayer *settingLayer;
};
#endif