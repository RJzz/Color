#include "HistoryLayer.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool HistoryLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	//设置背景图片
	/*auto spbk = Sprite::create("HelloWorld/background.jpg");
	spbk->setPosition(Point::ZERO);
	spbk->setAnchorPoint(Point::ZERO);
	this->addChild(spbk, 1);*/
	//背景目前用一个笨的办法：用menu吞并上一层的MenuItem点击事件
	auto bk = MenuItemImage::create("HelloWorld/background.jpg", "HelloWorld/background.jpg", CC_CALLBACK_1(HistoryLayer::menuCallBack, this));
	bk->setAnchorPoint(Vec2(0, 0));
	bk->setPosition(Point(0, 0));



	//设置对手机按键的监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(HistoryLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	//返回按钮
	auto rtButton = MenuItemImage::create("back-icon.png", "back-icon.png", CC_CALLBACK_1(HistoryLayer::menuCallBack, this));
	rtButton->setPosition(Point(46, 794));
	rtButton->setTag(10);
	auto menu = Menu::create(bk, rtButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	
	/*auto callback = [](Touch *, Event *){
		return true;
	};
	
	auto listener = EventListenerTouchOneByOne::create();
	
	listener->onTouchBegan = callback;

	listener->setSwallowTouches(true);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/

	loadRank();
	return true;	
}
 
void HistoryLayer::menuCallBack(Ref *s) {
	auto nowItem = (MenuItem *)s;
	switch (nowItem->getTag()) {
	case 10:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		this->removeFromParent();
		break;
	default:
		break;
	}
}
void HistoryLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
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

//初始化排行榜
void HistoryLayer::loadRank() {

	//积分模式排行
	auto rank1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("back1.png"));
	rank1->setPosition(273, 663);
	this->addChild(rank1, 2);

	//时间模式排行
	auto rank2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("back2.png"));
	rank2->setPosition(205, 427);
	this->addChild(rank2, 2);

	//街机模式排行
	auto rank3 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("back3.png"));
	rank3->setPosition(273, 190);
	this->addChild(rank3, 2);

	for (int i = 0; i < 3; i++) {
		int score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, i).c_str(), 0);
		auto label = Label::createWithBMFont("scoreRank.fnt", "0");
		label->setString(String::createWithFormat("%d", score)->_string);
		label->setPosition(309, 700 - i * 55);
		addChild(label, 3);
	}	
	for (int i = 0; i < 3; i++) {
		int score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_TIME, i).c_str(), 0);
		auto label = Label::createWithBMFont("scoreRank.fnt", "0");
		label->setString(String::createWithFormat("%d", score)->_string);
		label->setPosition(243, 463 - i * 55);
		addChild(label, 3);
	}
	for (int i = 0; i < 3; i++) {
		int score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_TOOLS, i).c_str(), 0);
		auto label = Label::createWithBMFont("scoreRank.fnt", "0");
		label->setString(String::createWithFormat("%d", score)->_string);
		label->setPosition(309, 228 - i * 55);
		addChild(label, 3);
	}
	
}