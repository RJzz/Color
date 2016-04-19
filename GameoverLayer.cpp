#include "GameoverLayer.h"
#include "GameSceneScore.h"
#include "GameSceneTime.h"
#include "GameSceneTools.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool GameoverLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	//背景目前用一个笨的办法：用menu吞并上一层的MenuItem点击事件
	auto bg = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_1(GameoverLayer::menuCallBack, this));
	bg->setOpacity(100);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(0, 0);


	//一些按钮

	//回到开始页面
	auto homeItem = MenuItemImage::create("home.png", "home.png", CC_CALLBACK_1(GameoverLayer::menuCallBack, this));
	//重新开始
	auto restartItem = MenuItemImage::create("again.png", "again.png", CC_CALLBACK_1(GameoverLayer::menuCallBack, this));
	//设置界面
	auto settingItem = MenuItemImage::create("rank.png", "rank.png", CC_CALLBACK_1(GameoverLayer::menuCallBack, this));
	

	homeItem->setTag(11);
	restartItem->setTag(12);
	settingItem->setTag(13);


	homeItem->setPosition(162, 310);
	restartItem->setPosition(245, 297);
	settingItem->setPosition(326, 310);


	auto menu1 = Menu::create(bg, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);


	auto menu = Menu::create(homeItem, restartItem, settingItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);


	auto gameover = Sprite::create("gameover.png");
	gameover->setPosition(240, 500);
	this->addChild(gameover, 2);


	auto New = Sprite::create("new.png");
	New->setTag(25);
	New->setPosition(336, 377);
	New->setVisible(false);
	this->addChild(New, 10);
	//对分数进行排序
	rank();


	//分数显示
	auto score = Label::createWithBMFont("scoreRank.fnt", "0");
	score->setString(String::createWithFormat("%d", UserDefault::getInstance()->getIntegerForKey(NEW_SCORE))->_string);
	score->setPosition(264, 400);
	this->addChild(score, 3);

	return true;
}


void GameoverLayer::menuCallBack(Ref* pSender) {
	MenuItem *nowItem = (MenuItem *)pSender;
	switch (nowItem->getTag()) {
	case 11:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		log("返回欢迎界面");
		this->removeFromParent();
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(0.5f, HelloWorld::createScene()));
		break;
		
	case 12:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		//重新开始游戏
		
		this->removeFromParent();

		//积分模式
		if (HelloWorld::mode == 1) {
			HelloWorld::life = 5;
			Director::getInstance()->replaceScene(GameSceneScore::createScene());
		}
		//时间模式
		else if (HelloWorld::mode == 2) {
			HelloWorld::life = 5;
			Director::getInstance()->replaceScene(GameSceneTime::createScene());
		}
		//街机模式
		else if (HelloWorld::mode == 3) {
			HelloWorld::life = 5;
			Director::getInstance()->replaceScene(GameSceneTools::createScene());
		}
		break;
	case 13:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		//进入游戏的排行界面
		history = HistoryLayer::create();
		this->addChild(history, 11);
		break;
	default:
		break;
	}
}

//排名
void GameoverLayer::rank() {
	auto New = this->getChildByTag(25);
	int i;
	std::vector<int> scoreList;
	//积分模式
	if (HelloWorld::mode == 1) {
		i = GameSceneScore::scoreS;
		UserDefault::getInstance()->setIntegerForKey(NEW_SCORE, GameSceneScore::scoreS);
		scoreList.push_back(i);
		for (int i = 0; i < 3; i++) {
			int score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, i).c_str(), 0);
			scoreList.push_back(score);
		}
		std::sort(scoreList.begin(), scoreList.end(), [](int &a, int &b){
			return a > b;
		});
		int rank = 0;
		for (auto i = scoreList.begin(); i != scoreList.end(); i++) {
			UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, rank).c_str(), *i);
			rank++;
		}
		if (UserDefault::getInstance()->getIntegerForKey(NEW_SCORE, GameSceneScore::scoreS) == UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_SCORE, 0).c_str(), 0)) {
			New->setVisible(true);
			if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
				SimpleAudioEngine::getInstance()->playEffect("sound/break.mp3");
			}
		}
	}
	//时间模式
	else if (HelloWorld::mode == 2) {
		i = GameSceneTime::scoreT;
		UserDefault::getInstance()->setIntegerForKey(NEW_SCORE, GameSceneTime::scoreT);
		scoreList.push_back(i);
		for (int i = 0; i < 3; i++) {
			int score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_TIME, i).c_str(), 0);
			scoreList.push_back(score);
		}
		std::sort(scoreList.begin(), scoreList.end(), [](int &a, int &b){
			return a > b;
		});
		int rank = 0;
		for (auto i = scoreList.begin(); i != scoreList.end(); i++) {
			UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d", RANK_TIME, rank).c_str(), *i);
			rank++;
		}
		if (UserDefault::getInstance()->getIntegerForKey(NEW_SCORE, GameSceneTime::scoreT) == UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_TIME, 0).c_str(), 0)) {
			New->setVisible(true);
			if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
				SimpleAudioEngine::getInstance()->playEffect("sound/break.mp3");
			}
		}
	}
	//街机模式
	else if (HelloWorld::mode == 3) {
		i = GameSceneTools::scoreTool;
		UserDefault::getInstance()->setIntegerForKey(NEW_SCORE, GameSceneTools::scoreTool);
		scoreList.push_back(i);
		for (int i = 0; i < 3; i++) {
			int score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_TOOLS, i).c_str(), 0);
			scoreList.push_back(score);
		}
		std::sort(scoreList.begin(), scoreList.end(), [](int &a, int &b){
			return a > b;
		});
		int rank = 0;
		for (auto i = scoreList.begin(); i != scoreList.end(); i++) {
			UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d", RANK_TOOLS, rank).c_str(), *i);
			rank++;
		}
		if (UserDefault::getInstance()->getIntegerForKey(NEW_SCORE, GameSceneTools::scoreTool) == UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RANK_TOOLS, 0).c_str(), 0)) {
			New->setVisible(true);
			if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
				SimpleAudioEngine::getInstance()->playEffect("sound/break.mp3");
			}
		}
	}
}
