#include "ToolsLayer.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool ToolsLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	this->schedule(schedule_selector(ToolsLayer::addTools), 10);
	this->scheduleUpdate();
	return true;
}

//??????
void ToolsLayer::addTools(float t) {
	Tools *pTools = Tools::create();
	int random = CCRANDOM_0_1() * 13 + 1;
	switch (random) {
	case 1:
	case 2:
	case 3:
		pTools->setToolsType(DoubleScore);
		pTools->setTag(DoubleScore);
		break;
	case 4:
	case 5:
	case 6:
		pTools->setToolsType(Life);
		pTools->setTag(Life);
		break;
	case 7:
	case 8:
	case 9:
		pTools->setToolsType(Strong);
		pTools->setTag(Strong);
		break;
	case 10:
	case 11:
		pTools->setToolsType(Clean);
		pTools->setTag(Clean);
		break;
	case 12:
	case 13:
		pTools->setToolsType(Ice);
		pTools->setTag(Ice);
		break;
	default:
		break;
	}
	this->addChild(pTools);
	vecTools.pushBack(pTools);
	auto actionMove = MoveTo::create(6, Point(pTools->getPositionX(), 200));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(ToolsLayer::removeTool, this));
	Sequence *sq = Sequence::create(actionMove, actionDone, NULL);
	pTools->runAction(sq);
}

//???????
void ToolsLayer::removeTool(Node* pNode) {
	Tools *sp = (Tools *)pNode;
	if (sp != NULL) {
		this->removeChild(sp, true);
		vecTools.eraseObject(sp);
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("clickorover.wav");
		}
	}
}


void ToolsLayer::update(float t) {

}


