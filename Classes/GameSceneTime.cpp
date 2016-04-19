#include "GameSceneTime.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
int GameSceneTime::scoreT = 0;
bool GameSceneTime::init() {
	if (!Layer::init()) {
		return false;
	}
	Director::getInstance()->resume();
	//��ʼ������Ϊ0
	scoreT = 0;

	//��ʼ��ʱ��Ϊ60��
	time = 60;

	//ģʽΪʱ��ģʽ
	HelloWorld::mode = 2;

	//���ñ���ͼƬ
	auto spbk = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.jpg"));
	spbk->setPosition(Point::ZERO);
	spbk->setAnchorPoint(Point::ZERO);
	this->addChild(spbk);

	//������
	auto machine = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("machine.png"));
	machine->setPosition(240, 65);
	this->addChild(machine);

	//��~~
	auto line = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("line.png"));
	line->setPosition(240, 112);
	this->addChild(line);

	//��������
	auto scoreB = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("score.png"));
	scoreB->setPosition(65, 811);
	this->addChild(scoreB);

	//������ʾ
	auto score = Label::createWithBMFont("scoreLabel.fnt", "0");
	score->setTag(100);
	score->setPosition(80, 811);
	this->addChild(score);
	//labScore->setString(String::createWithFormat("%d", score)->_string);


	//����ʱ
	auto time = Label::createWithBMFont("time.fnt", "60");
	time->setColor(Color3B::GREEN);
	time->setTag(101);
	time->setPosition(240, 800);
	this->addChild(time);


	//��ͣ��ť
	auto pause = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_1(GameSceneTime::menuCallBack, this));
	pause->setPosition(415, 811);
	pause->setTag(10);
	auto menu = Menu::create(pause, NULL);
	menu->setAnchorPoint(Vec2(0.5, 0.5));
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	this->schedule(schedule_selector(GameSceneTime::timeMinus), 1);
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
//������ӵ�������
Scene * GameSceneTime::createScene() {
	auto scene = Scene::create();
	auto layer = GameSceneTime::create();
	scene->addChild(layer);
	return scene;
}

void GameSceneTime::onEnterTransitionDidFinish() {
	monsterLayer = MonsterLayer::create();
	this->addChild(monsterLayer, 1);
	ballLayer = (BallLayer *)BallLayer::create();
	ballLayer->setPosition(Point::ZERO);
	ballLayer->setAnchorPoint(Point::ZERO);
	this->addChild(ballLayer, 2);
}


void GameSceneTime::update(float t) {
	//��ȡ��������ʾLabel
	auto score = (Label *)this->getChildByTag(100);
	score->setString(String::createWithFormat("%d", scoreT)->_string);
	//С�������֮�����ײ���
	for (int i = 0; i < monsterLayer->vecMonster.size(); i++) {
		auto monster = monsterLayer->vecMonster.at(i);
		for (int j = 0; j < BallLayer::getBalls()->size(); j++) {
			auto ball = BallLayer::getBalls()->at(j);
			if (monster->getBoundingBox().intersectsRect(ball->getBoundingBox()) && ball->isShoot == true) {
				if (monster->getColor() == ball->getColor()) {
					switch (monster->getTag()) {
						//���ײ�����Ǻ죬�ƣ������������1
					case MonsterRed:
					case MonsterYellow:
					case MonsterBlue:
						scoreT += monster->getScore();
						break;
						//�����ײ�������ϣ��ȣ��̣��������3
					case MonsterPurple:
					case MonsterOrange:
					case MonsterGreen:
						scoreT += monster->getScore();
						break;
						//���ײ�����Ǻ�ɫ���������5
					case MonsterBlack:
						scoreT += monster->getScore();
						break;
					default:
						break;
					}

					//�ڹ��޲����Ƴ���ǰ����
					monsterLayer->removeAnimation(monster->getColor(), monster);
					monsterLayer->removeMonster(monster);
					//��������Ƴ���ǰ��С��
					ballLayer->removeBall(ball);
					//��������1
					i--;
					break;
				}
			}
		}
	}
}


//��ť�Ļص�����
void GameSceneTime::menuCallBack(Ref* pSender) {
	MenuItem *nowItem = (MenuItem *)pSender;
	switch (nowItem->getTag()) {
	case 10:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		//��ͣ
		Director::getInstance()->pause();
		//������ͣ��
		pauseLayer = PauseLayer::create();
		//����ͣ����ӵ�������
		this->addChild(pauseLayer, 3);
		break;
	default:
		break;
	}
}

void GameSceneTime::timeMinus(float t) {
	auto timeLabel = (Label*)this->getChildByTag(101);
	if (time > 10){
		time--;
		//labScore->setString(String::createWithFormat("%d", score)->_string);
	}
	else if (time > 0 && time <= 10) {
		time--;
		timeLabel->setColor(Color3B::RED);
	}
	else if (time == 0) {
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/over.mp3");
		}
		//��Ϸ���������������Ϸ������
		Director::getInstance()->pause();
		//����gameover��
		gameoverLayer = GameoverLayer::create();

		//��gameover����ӵ���������
		this->addChild(gameoverLayer, 3);
		
	}
	timeLabel->setString(String::createWithFormat("%d", time)->_string);
}