#include "LoadScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
USING_NS_CC;
using namespace CocosDenshion;
bool LoadScene::init() {
	if (!Layer::init()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameElement.plist");
	auto bcc = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("welcome.jpg"));
	bcc->setPosition(Point(0, 0));
	bcc->setAnchorPoint(Vec2(0, 0));
	this->addChild(bcc, 9);

	this->scheduleOnce(schedule_selector(LoadScene::updateOnce), 0.0f);
	return true;
}

Scene* LoadScene::createScene() {
	auto layer = LoadScene::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}

//加载完成之后调用函数updateOnce跳转至主页面
void LoadScene::updateOnce(float t) {

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("monster.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ball.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tools.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Life.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("black.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("create.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("frozen.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("walk.plist");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("mainbc.ogg");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("secondmain.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/select.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/boom.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/over.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/break.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/boom.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/shoot.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/ice.wav");
	//如果用户是第一次进入的话，音效默认开启，将历史排名的数据全部初始化,
	if (!UserDefault::getInstance()->getBoolForKey(FIRST, false)) {
		UserDefault::getInstance()->setBoolForKey(SOUND, true);
		UserDefault::getInstance()->setBoolForKey(FIRST, true);
		for (int i = 0; i < 3; i++) {

			UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, i).c_str(), 0);
			UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d", RANK_TIME, i).c_str(), 0);
			UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d", RANK_TOOLS, i).c_str(), 0);
			UserDefault::getInstance()->setIntegerForKey(NEW_SCORE, 0);
		}
	}
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, HelloWorld::createScene()));
}

void LoadScene::onEnterTransitionDidFinish() {

	//Director::getInstance()->replaceScene(HelloWorld::createScene());
}