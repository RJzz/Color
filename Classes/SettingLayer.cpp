#include"SettingLayer.h"
#include"HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
using namespace CocosDenshion;
bool SettingLayer::init() {
	if (!Layer::init()) {
		return false;
	}


	//设置背景图片
	//auto spbk = Sprite::create("HelloWorld/background.jpg");
	auto spbk = MenuItemImage::create("HelloWorld/background.jpg", "HelloWorld/background.jpg", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
	spbk->setPosition(Point::ZERO);
	spbk->setAnchorPoint(Point::ZERO);


	//this->addChild(spbk);
	//设置对手机按键的监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(SettingLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//返回按钮
	auto returnItem = MenuItemImage::create("back-icon.png", "back-icon.png", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
	returnItem->setPosition(Point(47.5, 750));
	returnItem->setTag(10);
	//跳转至关于页面
	auto aboutItem = MenuItemImage::create("about-button.png", "about-button.png", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
	aboutItem->setPosition(Point(240, 262));
	aboutItem->setTag(13);

	//检查更新
	auto checkItem = MenuItemImage::create("check-button.png", "check-button.png", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
	checkItem->setPosition(Point(240, 360));
	checkItem->setTag(14);

	auto setback = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("set1-back.png"));
	setback->setPosition(Point(240, 533));
	this->addChild(setback, 2);
	if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
		on1 = MenuItemImage::create("on-click.png", "on-click.png", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
		off1 = MenuItemImage::create("off-icon.png", "off-icon.png", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
	}
	else {
		on1 = MenuItemImage::create("on-icon.png", "on-icon.png", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
		off1 = MenuItemImage::create("off-click.png", "off-click.png", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
	}
	on1->setPosition(258, 550);
	off1->setPosition(333, 550);
	on1->setTag(110);
	off1->setTag(111);


	if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
		on2 = MenuItemImage::create("on-click.png", "on-click.png", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
		off2 = MenuItemImage::create("off-icon.png", "off-icon.png", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
	}
	else {
		on2 = MenuItemImage::create("on-icon.png", "on-icon.png", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
		off2 = MenuItemImage::create("off-click.png", "off-click.png", CC_CALLBACK_1(SettingLayer::menuCallBack, this));
	}
	on2->setPosition(258, 470);
	off2->setPosition(333, 470);
	on2->setTag(112);
	off2->setTag(113);
	auto click = Menu::create(on1, on2, off1, off2, NULL);
	click->setPosition(Vec2::ZERO);
	this->addChild(click, 3);

	auto bkmenu = Menu::create(spbk, NULL);
	bkmenu->setPosition(Vec2::ZERO);
	this->addChild(bkmenu, 1);
	auto menu = Menu::create(aboutItem, returnItem, checkItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);
	return true;
}

void SettingLayer::menuCallBack(Ref* pSender) {
	auto nowItem = (MenuItem *)pSender;
	switch (nowItem->getTag()) {
	case 10:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		//将当前设置层从父节点中删除
		this->removeFromParent();
		break;
	case 13:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		aboutLayer = AboutLayer::create();
		this->addChild(aboutLayer, 3);
		break;
	case 110:
		
		if (!UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
			UserDefault::getInstance()->setBoolForKey(SOUND, true);
			on1->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("on-click.png"));
			on1->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("on-click.png"));
			off1->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("off-icon.png"));
			off1->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("off-icon.png"));
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
		else {
			break;
		}
		break;
	case 111:
		
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			UserDefault::getInstance()->setBoolForKey(SOUND, false);
			on1->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("on-icon.png"));
			on1->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("on-icon.png"));
			off1->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("off-click.png"));
			off1->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("off-click.png"));
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
		else {
			break;
		}
		break;
	case 112:
		break;
	case 113:
		break;
	default:
		break;
	}
}
void SettingLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
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