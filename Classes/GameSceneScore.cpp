#include "GameSceneScore.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
int GameSceneScore::scoreS = 0;
bool GameSceneScore::init() {
	if (!Layer::init()) {
		return false;
	}
	HelloWorld::life = 5;
	Director::getInstance()->resume();
	//初始化分数为0
	scoreS = 0;

	//模式为积分模式
	HelloWorld::mode = 1;

	//设置背景图片
	auto spbk = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.jpg"));
	spbk->setPosition(Point::ZERO);
	spbk->setAnchorPoint(Point::ZERO);	
	this->addChild(spbk);
	
	//生命值
	auto life = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("life5.png"));
	life->setPosition(240, 120);
	life->setTag(500);
	this->addChild(life);

	//机器人
	auto machine = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("machine.png"));
	machine->setPosition(240, 65);
	this->addChild(machine);

	//线~~
	auto line = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("line.png"));
	line->setPosition(240, 112);	
	this->addChild(line);

	//分数背景
	auto scoreB = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("score.png"));
	scoreB->setPosition(65, 811);
	this->addChild(scoreB);

	//分数显示
	auto score = Label::createWithBMFont("scoreLabel.fnt", "0");
	score->setTag(100);
	score->setPosition(80, 811);
	this->addChild(score);
	//labScore->setString(String::createWithFormat("%d", score)->_string);


	//暂停按钮
	auto pause = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_1(GameSceneScore::menuCallBack, this));
	pause->setPosition(415, 811);
	pause->setTag(10);
	auto menu = Menu::create(pause, NULL);
	menu->setAnchorPoint(Vec2(0.5, 0.5));
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	this->scheduleUpdate();
	if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("secondmain.mp3", true);
	}
	else if (!UserDefault::getInstance()->getBoolForKey(SOUND)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("secondmain.mp3", true);
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	return true;

}
//将层添加到场景中
Scene * GameSceneScore::createScene() {
	auto scene = Scene::create();
	auto layer = GameSceneScore::create();
	scene->addChild(layer);
	return scene;
}

void GameSceneScore::onEnterTransitionDidFinish() {
	monsterLayer = MonsterLayer::create();
	this->addChild(monsterLayer, 1);
	ballLayer = (BallLayer *)BallLayer::create();
	ballLayer->setPosition(Point::ZERO);
	ballLayer->setAnchorPoint(Point::ZERO);
	this->addChild(ballLayer, 2);
}
void GameSceneScore::update(float t) {
	//更新生命值
	auto life = (Sprite *)this->getChildByTag(500);
	switch (HelloWorld::life) {
	case 5:
		life->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("life5.png"));
		break;
	case 4:
		life->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("life4.png"));
		break;
	case 3:
		life->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("life3.png"));
		break;
	case 2:
		life->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("life2.png"));
		break;
	case 1:
		life->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("life1.png"));
		break;
	default:
		break;
	}
	if (HelloWorld::life <= 0) {
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/over.mp3");
		}
		//游戏结束，进入添加游戏结束层
		Director::getInstance()->pause();
		//创建gameover层
		gameoverLayer = GameoverLayer::create();
		this->unscheduleUpdate();
		//将gameover层添加到场景当中
		this->addChild(gameoverLayer, 4);
	}

	//获取到分数显示Label
	auto score = (Label *)this->getChildByTag(100);
	score->setString(String::createWithFormat("%d", scoreS)->_string);
	//小球与怪兽之间的碰撞检测
	for (int i = 0; i < monsterLayer->vecMonster.size(); i++) {
		auto monster = monsterLayer->vecMonster.at(i);
		for (int j = 0; j < BallLayer::getBalls()->size(); j++) {
			auto ball = BallLayer::getBalls()->at(j);
			if (monster->getBoundingBox().intersectsRect(ball->getBoundingBox()) && ball->isShoot == true) {
				if (monster->getColor() == ball->getColor()) {
					switch (monster->getTag()) {
					//如果撞到的是红，黄，蓝，则分数加1
					case MonsterRed:
					case MonsterYellow:
					case MonsterBlue:
						scoreS += monster->getScore();
						break;
					//如果是撞到的是紫，橙，绿，则分数加3
					case MonsterPurple:
					case MonsterOrange:
					case MonsterGreen:
						scoreS += monster->getScore();
						break;
					//如果撞到的是黑色球，则分数加5
					case MonsterBlack:
						scoreS += monster->getScore();
						break;
					default:
						break;
					}

					//在怪兽层中移除当前怪兽
					monsterLayer->removeAnimation(monster->getColor(), monster);
					monsterLayer->removeMonster(monster);
					//在球层中移除当前的小球
					ballLayer->removeBall(ball);
					//计数器减1
					i--;
					break;
				}
			}
		}
	}	
}


//按钮的回调方法
void GameSceneScore::menuCallBack(Ref* pSender) {
	MenuItem *nowItem = (MenuItem *)pSender;
	switch (nowItem->getTag()) {
	case 10:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		//暂停
		Director::getInstance()->pause();
		//创建暂停层
		pauseLayer = PauseLayer::create();
		//将暂停层添加到场景中
		this->addChild(pauseLayer, 3);
		break;
	default:
		break;
	}
}


