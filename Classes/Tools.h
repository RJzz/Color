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
	Rect getBoundingBox();							//��ȡ�����ĵ��߾���ľ��α߽�
	Sprite* getSprite();							//��ȡ�����ĵ��߾���								
	Point getcurPoint();							//��ȡ�������ڵ�λ��
public:
	Sprite* pTools;
};
#endif