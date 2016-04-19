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
	//��ʼ������Ϊ0
	scoreS = 0;

	//ģʽΪ����ģʽ
	HelloWorld::mode = 1;

	//���ñ���ͼƬ
	auto spbk = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.jpg"));
	spbk->setPosition(Point::ZERO);
	spbk->setAnchorPoint(Point::ZERO);	
	this->addChild(spbk);
	
	//����ֵ
	auto life = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("life5.png"));
	life->setPosition(240, 120);
	life->setTag(500);
	this->addChild(life);

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


	//��ͣ��ť
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
//������ӵ�������
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
	//��������ֵ
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
		//��Ϸ���������������Ϸ������
		Director::getInstance()->pause();
		//����gameover��
		gameoverLayer = GameoverLayer::create();
		this->unscheduleUpdate();
		//��gameover����ӵ���������
		this->addChild(gameoverLayer, 4);
	}

	//��ȡ��������ʾLabel
	auto score = (Label *)this->getChildByTag(100);
	score->setString(String::createWithFormat("%d", scoreS)->_string);
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
						scoreS += monster->getScore();
						break;
					//�����ײ�������ϣ��ȣ��̣��������3
					case MonsterPurple:
					case MonsterOrange:
					case MonsterGreen:
						scoreS += monster->getScore();
						break;
					//���ײ�����Ǻ�ɫ���������5
					case MonsterBlack:
						scoreS += monster->getScore();
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
void GameSceneScore::menuCallBack(Ref* pSender) {
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


