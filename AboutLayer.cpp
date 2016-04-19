#include"AboutLayer.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
using namespace CocosDenshion;
bool AboutLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	//���ñ���ͼƬ
	auto spbk = MenuItemImage::create("about.jpg", "about.jpg", CC_CALLBACK_1(AboutLayer::menuCallBack, this));
	spbk->setPosition(Point::ZERO);
	spbk->setAnchorPoint(Point::ZERO);

	//���ö��ֻ������ļ���
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(AboutLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//���ذ�ť
	auto returnItem = MenuItemImage::create("back-icon.png", "back-icon.png", CC_CALLBACK_1(AboutLayer::menuCallBack, this));
	returnItem->setPosition(Point(47.5, 750));
	returnItem->setTag(10);
	auto menu = Menu::create(spbk, returnItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 9);

	return true;
}

void AboutLayer::menuCallBack(Ref* pSender) {
	auto nowItem = (MenuItem *)pSender;
	switch (nowItem->getTag()) {
	case 10:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		this->removeFromParent();
		break;
	}
}

void AboutLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_BACK:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		this->removeFromParent();
		break;
	default:
		break;
	}
}