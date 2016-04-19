#ifndef __HISTORY_LAYER_H__
#define __HISTORY_LAYER_H__
#include "cocos2d.h"
using namespace cocos2d;
class HistoryLayer : public Layer{
public:
	bool init();
	void menuCallBack(Ref* pSender);
	CREATE_FUNC(HistoryLayer);
	static Scene * createScene();
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);   //处理手机按键
	void loadRank();													//初始化排行榜
};
#endif