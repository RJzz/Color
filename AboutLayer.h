#ifndef __ABOUT_LAYER_H__
#define __ABOUT_LAYER_H__
#include "cocos2d.h"
using namespace cocos2d;
class AboutLayer : public Layer{
public:
	bool init();
	void menuCallBack(Ref* pSender);
	CREATE_FUNC(AboutLayer);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//处理手机按键
};
#endif