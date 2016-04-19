#ifndef _TOOLS_H_
#define _TOOLS_H_
#include "cocos2d.h"
USING_NS_CC;
enum ToolsType {
	Clean = 1,
	Strong,
	DoubleScore,
	Ice,
	Life
};
class Tools : public Node {
public:
	CREATE_FUNC(Tools);
	void setToolsType(ToolsType s);
	Rect getBoundingBox();							//获取创建的道具精灵的矩形边界
	Sprite* getSprite();							//获取创建的道具精灵								
	Point getcurPoint();							//获取道具现在的位置
public:
	Sprite* pTools;
};
#endif