#include "HelloWorldScene.h"
#include "GameSceneScore.h"
#include "GameSceneTime.h"
#include "GameSceneTools.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
using namespace std;
int HelloWorld::life = 10;
bool HelloWorld::unStoppable = false;
bool HelloWorld::isDouble = false;
Scene* HelloWorld::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
//初始化游戏模式判定变量
int HelloWorld::mode = 0;
// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }

	

	HelloWorld::life = 5;




    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Logo


	//跳转至历史排行按钮
    auto toHistoryItem = MenuItemImage::create("HelloWorld/history1.png", "HelloWorld/history2.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
	toHistoryItem->setPosition(70, 59);
	toHistoryItem->setTag(10);
	//设置按钮
	auto settingItem = MenuItemImage::create("HelloWorld/setting1.png", "HelloWorld/setting2.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
	settingItem->setPosition(410, 59);
	settingItem->setTag(11);
	//选择模式按钮
	auto scoreItem = MenuItemImage::create("HelloWorld/score1.png", "HelloWorld/score2.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
	auto timeItem = MenuItemImage::create("HelloWorld/time1.png", "HelloWorld/time2.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
	auto toolsItem = MenuItemImage::create("HelloWorld/tools1.png", "HelloWorld/tools2.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
	scoreItem->getSelectedImage()->setAnchorPoint(Vec2(0.12, 0.1));
	timeItem->getSelectedImage()->setAnchorPoint(Vec2(0.12, 0.1));
	toolsItem->getSelectedImage()->setAnchorPoint(Vec2(0.12, 0.1));
	scoreItem->setTag(12);
	timeItem->setTag(13);
	toolsItem->setTag(14);
	scoreItem->setPosition(Point(240, 369));
	timeItem->setPosition(Point(240, 261));
	toolsItem->setPosition(Point(240, 153));
	// create menu, it's an autorelease object
	auto menu = Menu::create(settingItem, toHistoryItem, scoreItem, timeItem, toolsItem, NULL);
	menu->setTag(100);
	menu->setAnchorPoint(Vec2(0.5, 0.5));
	menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    auto sprite = Sprite::create("HelloWorld/background.jpg");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
	auto logo = Sprite::create("HelloWorld/logo.png");
	logo->setPosition(Point(242, 639));
	this->addChild(logo);
	this->scheduleUpdate();
	if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("mainbc.ogg", true);
	}

    return true;
}



void HelloWorld::menuCallback(Ref* pSender) {
	MenuItem *nowItem = (MenuItem *)pSender;
	switch (nowItem->getTag()) {
	case 10:

		//跳转到历史排行场景
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		historyLayer = HistoryLayer::create();
		this->addChild(historyLayer, 2);
		break;
	case 11:
		//添加设置层到场景中
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		settingLayer = SettingLayer::create();
		this->addChild(settingLayer, 2);
		break;
	case 12:
		//跳转到积分模式场景
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		Director::getInstance()->replaceScene(GameSceneScore::createScene());
		break;
	case 13:
		//跳转到时间吗模式场景
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		Director::getInstance()->replaceScene(GameSceneTime::createScene());
		break;
	case 14:
		//跳转到街机模式场景
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		Director::getInstance()->replaceScene(GameSceneTools::createScene());
		break;
	default:
		break;
	}
}
void HelloWorld::update(float t) {
	/*Menu *menu = (Menu *)this->getChildByTag(100);
	if (historyLayer->isVisible() || historyLayer->isVisible()) {
		
		menu->setEnabled(false);
	}
	else {
		menu->setEnabled(true);
	}



	/*if (hh == true) {
		MenuItemImage *s = (MenuItemImage *)this->getChildByTag(12);
		s->setPosition(240, 369);
	}*/

	/*auto *score3 = (MenuItemSprite *)this->getChildByTag(12);
	if (score3->isSelected()) {
		score3->setPosition(240, 402);
	}*/
}


void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_BACK:
		//if (readyEnd == true) {
		Director::getInstance()->end();
		//}
		readyEnd = true;
		this->unschedule(schedule_selector(HelloWorld::changeReady));
		this->scheduleOnce(schedule_selector(HelloWorld::changeReady), 2.0f);
		break;
	default:
		break;
	}
}


void HelloWorld::changeReady(float t) {
	if (readyEnd == true) {
		readyEnd = false;
	}
}
