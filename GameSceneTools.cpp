#include "GameSceneTools.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
int GameSceneTools::scoreTool = 0;

bool GameSceneTools::init() {
	if (!Layer::init()) {
		return false;
	}
	Director::getInstance()->resume();

	HelloWorld::unStoppable = false;
	HelloWorld::isDouble = false;
	//��ʼ������Ϊ5
	HelloWorld::life = 5;

	//��ʼ������Ϊ0
	scoreTool = 0;

	//ģʽΪ����ģʽ
	HelloWorld::mode = 3;

	//��ը����
	auto ps = ParticleSystemQuad::create("hitBoom.plist");
	ps->setVisible(false);
	ps->setPosition(Point(480, 50));
	ps->setTag(666);
	this->addChild(ps, 10);
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
	auto line = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("linetool.png"));
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

	//���
	auto clean = MenuItemImage::create("clean-icon.png", "clean-icon.png", CC_CALLBACK_1(GameSceneTools::menuCallBack, this));
	clean->setPosition(400, 132);
	clean->setTag(11);

	//������ߵ�����
	auto cleanNumber = Label::createWithBMFont("scoreLabel.fnt", "0");
	cleanNumber->setColor(Color3B::RED);
	cleanNumber->setPosition(380, 140);
	cleanNumber->setOpacity(200);
	cleanNumber->setTag(1001);
	this->addChild(cleanNumber, 3);


	//����
	auto ice = MenuItemImage::create("ice-icon.png", "ice-icon.png", CC_CALLBACK_1(GameSceneTools::menuCallBack, this));
	ice->setPosition(80, 132);
	ice->setTag(12);

	//�������ߵ�����
	auto iceNumber = Label::createWithBMFont("scoreLabel.fnt", "0");
	iceNumber->setColor(Color3B::RED);
	iceNumber->setPosition(100, 140);
	iceNumber->setOpacity(200);
	iceNumber->setTag(1002);
	this->addChild(iceNumber, 3);

	//��ͣ��ť
	auto pause = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_1(GameSceneTools::menuCallBack, this));
	pause->setPosition(415, 811);
	pause->setTag(10);
	auto menu = Menu::create(clean, pause, ice, NULL);
	menu->setAnchorPoint(Vec2(0.5, 0.5));
	menu->setPosition(Vec2::ZERO);


	this->addChild(menu, 1);

	this->schedule(schedule_selector(GameSceneTools::control), 1);
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
Scene * GameSceneTools::createScene() {
	auto scene = Scene::create();
	auto layer = GameSceneTools::create();
	scene->addChild(layer);
	return scene;
}

void GameSceneTools::onEnterTransitionDidFinish() {
	monsterLayer = MonsterLayer::create();
	this->addChild(monsterLayer, 1);
	ballLayer = (BallLayer *)BallLayer::create();
	ballLayer->setPosition(Point::ZERO);
	ballLayer->setAnchorPoint(Point::ZERO);
	this->addChild(ballLayer, 2);
	toolsLayer = ToolsLayer::create();
	this->addChild(toolsLayer, 3);
}



void GameSceneTools::update(float t) {
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
	//���±������ߵ�����
	auto iceNumber = (Label *)this->getChildByTag(1002);
	iceNumber->setString(String::createWithFormat("%d", ice.size())->_string);

	//�����������ߵ�����
	auto cleanNumber = (Label *)this->getChildByTag(1001);
	cleanNumber->setString(String::createWithFormat("%d", clean.size())->_string);



	//��ȡ��������ʾLabel
	auto score = (Label *)this->getChildByTag(100);
	score->setString(String::createWithFormat("%d", scoreTool)->_string);
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
						//˫������
						if (HelloWorld::isDouble == true) {
							scoreTool += monster->getScore() * 2;
						}
						else {
							scoreTool += monster->getScore();
						}
						
						break;
					//�����ײ�������ϣ��ȣ��̣��������3
					case MonsterPurple:
					case MonsterOrange:
					case MonsterGreen:
						if (HelloWorld::isDouble == true) {
							scoreTool += monster->getScore() * 2;
						}
						else {
							scoreTool += monster->getScore();
						}
						break;
					//���ײ�����Ǻ�ɫ���������5
					case MonsterBlack:
						if (HelloWorld::isDouble == true) {
							scoreTool += monster->getScore() * 2;
						}
						else {
							scoreTool += monster->getScore();
						}
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
	for (int i = 0; i < toolsLayer->vecTools.size(); i++) {
		auto tool = toolsLayer->vecTools.at(i);
		for (int i = 0; i < BallLayer::getBalls()->size(); i++) {
			auto ball = BallLayer::getBalls()->at(i);
			if (tool->getBoundingBox().intersectsRect(ball->getBoundingBox()) && ball->isShoot == true) {
				switch (tool->getTag()) {
				case Clean:
					clean.pushBack(tool);
					break;
				case Strong:
					beingStrong();
					break;
				case Life:
					getLife();
					break;
				case DoubleScore:
					doubleScore();
					break;
				case Ice:
					ice.pushBack(tool);
					break;
				default:
					break;
				}

				//�ڵ��߲����Ƴ���ǰ����
				toolsLayer->removeTool(tool);
				//��������Ƴ���ǰ��С��
				ballLayer->removeBall(ball);
				//��������1
				i--;
				break;
			}
		}
	}

	//���Ѫ�����ڵ���0�������Ϸ������
	if (HelloWorld::life <= 0) {
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/over.mp3");
		}
		//��Ϸ���������������Ϸ������
		Director::getInstance()->pause();
		//����gameover��
		gameoverLayer = GameoverLayer::create();
		//��gameover����ӵ���������
		this->addChild(gameoverLayer, 5);
	}
	/*if (HelloWorld::life <= 0) {
		Director::getInstance()->pause();
		gameoverLayer = GameoverLayer::create();
		this->addChild(gameoverLayer, 3);
	}*/
}

void GameSceneTools::control(float t) {

	

	//���˫��״̬��������ʼ��ʱ
	if (HelloWorld::isDouble == true) {
		controlDouble++;
	}
	//�޷��赲״̬��ʼ����ʼ��ʱ
	if (HelloWorld::unStoppable == true) {
		controlStrong++;
	}

	//ʱ�����ı�״̬������ʱ�����������
	if (controlDouble == 6) {
		HelloWorld::isDouble = false;
		controlDouble = 0;
	}
	if (controlStrong == 6) {
		HelloWorld::unStoppable = false;
		controlStrong = 0;
	}
}
//��ť�Ļص�����
void GameSceneTools::menuCallBack(Ref* pSender) {
	MenuItem *nowItem = (MenuItem *)pSender;
	switch (nowItem->getTag()) {
	case 10:
		//��ͣ
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		Director::getInstance()->pause();
		//������ͣ��
		pauseLayer = PauseLayer::create();
		//����ͣ����ӵ�������
		this->addChild(pauseLayer, 4);
		break;
	case 11:
		cleanMonster();
		break;
	case 12:
		iceMonster();
		break;
	default:
		break;
	}
}

//˫��
void GameSceneTools::doubleScore() {
	//����ʱ����������
	controlDouble = 0;
	//�ı�״̬

	if (HelloWorld::isDouble == false) {
		HelloWorld::isDouble = true;
	}
}

//�������
void GameSceneTools::cleanMonster() {
	if (clean.size() > 0) {
		auto boom = this->getChildByTag(666);
		boom->setVisible(true);
		this->scheduleOnce(schedule_selector(GameSceneTools::boomControl), 2.0f);
		for (int i = 0; i < monsterLayer->vecMonster.size(); i++) {
			auto monster = monsterLayer->vecMonster.at(i);
			monsterLayer->changeCondition(monster);

			//iceAction(monster, monster->getColor());*/
			GameSceneTools::scoreTool += monster->getScore();
			monsterLayer->removeMonster(monster);
			
			i--;
		}
		clean.eraseObject(clean.at(clean.size() - 1));
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/boom.wav");
		}


	}
}

//��������
void GameSceneTools::iceMonster() {
	if (ice.size() > 0) {
		for (auto &monster : monsterLayer->vecMonster) {
			if (monster->frozen == false) {
				monster->pauseSchedulerAndActions();
				monster->pMonsterSprite->stopAllActions();
				auto ps = ParticleSystemQuad::create("hitIce.plist");
				ps->setPosition(Point(monster->getPositionX(), monster->getPositionY()));
				this->addChild(ps, 100);
				monster->pMonsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(monster->getColor() + "-frozee.png"));
				switch (monster->getTag()) {
				case MonsterRed:
					iceAction(monster, monster->getColor(), 26);

					break;
				case MonsterYellow:
					iceAction(monster, monster->getColor(), 26);
					break;
				case MonsterBlue:
					iceAction(monster, monster->getColor(), 28);

					break;
				case MonsterGreen:
					iceAction(monster, monster->getColor(), 26);
				case MonsterPurple:
					iceAction(monster, monster->getColor(), 26);
					break;
				case MonsterOrange:
					iceAction(monster, monster->getColor(), 28);
					break;
				case MonsterBlack:
					iceAction(monster, monster->getColor(), 26);
					break;
				default:
					break;
				}
				monster->scheduleOnce(schedule_selector(Monster::resumeWalk), 5.0f);
				//iceAction(monster, monster->getColor());
				monster->frozen = true;

			}
			else if (monster->frozen == true) {
				monster->unschedule(schedule_selector(Monster::resumeWalk));
				monster->scheduleOnce(schedule_selector(Monster::resumeWalk), 5.0f);
			}
			
		}
		ice.eraseObject(ice.at(ice.size() - 1));
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/ice.wav");
		}
	}
}

//�޵�״̬
void GameSceneTools::beingStrong() {
	//����ʱ����������
	controlStrong = 0;
	//�ı�״̬
	if (HelloWorld::unStoppable == false) {
		HelloWorld::unStoppable = true;
	}
}

//�������ҩˮ
void GameSceneTools::getLife() {

	//�������ֵС��10�Ļ�������ֵ��һ
	if (HelloWorld::life < 10) {
		HelloWorld::life++;
	}
}

//��������ִ�еĶ���Ч��
void GameSceneTools::iceAction(Monster *monster, string s, int number) {
	char a[30];
	string buff;
	Animation *panimation = Animation::create();
	panimation->setRestoreOriginalFrame(true);	//ִ��֮�󷵻�ԭ����״̬
	panimation->setDelayPerUnit(0.05f);			//ִ�е�ʱ��
	for (int id = 1; id <= number; id++) {
		sprintf(a, "%d", id);
		buff = s + "000000 (" + a + ").png";
		panimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(buff));
	}
	monster->pMonsterSprite->runAction(Animate::create(panimation));

	
}

void GameSceneTools::boomControl(float t) {
	auto boom = this->getChildByTag(666);
	if (boom->isVisible()) {
		boom->setVisible(false);
	}
}