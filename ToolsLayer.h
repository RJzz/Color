#ifndef _TOOLS_LAYE_H_
#define _TOOLS_LAYE_H_
#include "cocos2d.h"
#include "Tools.h"
USING_NS_CC;
using namespace cocos2d;
class ToolsLayer : public Layer {
public:
	bool init();
	CREATE_FUNC(ToolsLayer);
public:
	void addTools(float t);							//添加怪兽
	void removeTool(Node  *pNode);				    //移除道具
	void update(float t);
	void control(float t);
public:
	Vector<Tools* > vecTools;						//道具容器
	void f_removemyAnimation(Node* pNode);			//碰线之后，移除时候的时动画效果
};
#endif