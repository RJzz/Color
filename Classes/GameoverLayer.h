#ifndef _GAMEOVER_LAYER_H_
#define _GAMEOVER_LAYER_H_
#include "cocos2d.h"
#include "GameData.h"

#include "HistoryLayer.h"
using namespace cocos2d;
class GameoverLayer : public Layer {
public:
	bool init();
	CREATE_FUNC(GameoverLayer);
	void menuCallBack(Ref* pSender);
	void rank();
public:
	HistoryLayer *history;
};
#endif