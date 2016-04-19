#ifndef _LOAD_SCENE_H_
#define _LOAD_SCENE_H_
#include "cocos2d.h"
using namespace cocos2d;
class LoadScene : public Layer {
public:
	bool init();
	CREATE_FUNC(LoadScene);
	static Scene * createScene();
	void updateOnce(float t);
	virtual void onEnterTransitionDidFinish();
};
#endif;