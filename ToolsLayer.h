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
	void addTools(float t);							//��ӹ���
	void removeTool(Node  *pNode);				    //�Ƴ�����
	void update(float t);
	void control(float t);
public:
	Vector<Tools* > vecTools;						//��������
	void f_removemyAnimation(Node* pNode);			//����֮���Ƴ�ʱ���ʱ����Ч��
};
#endif