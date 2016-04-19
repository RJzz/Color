#include "MonsterLayer.h"
#include "HelloWorldScene.h"
#include "GameSceneTools.h"
#include "Vibrator.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;
bool MonsterLayer::init() {
	if (!Layer::init()) {
		return false;
		}


	this->schedule(schedule_selector(MonsterLayer::control), 1);
	this->scheduleUpdate();
	return true;
}
//添加怪兽
void MonsterLayer::addMonster(float t) {
	Monster *pMonster = Monster::create();
	int random = CCRANDOM_0_1() * 16 + 1;
	switch (random) {
	case 1:
	case 2:
	case 3:
		pMonster->setMonsterByType(MonsterRed);
		pMonster->setScore(MONSTER_RED_SCORE);
		pMonster->setColor(MONSTER_RED);
		pMonster->setTag(MonsterRed);
		break;
	case 4:
	case 5:
	case 6:
		pMonster->setMonsterByType(MonsterYellow);
		pMonster->setScore(MONSTER_YELLOW_SCORE);
		pMonster->setColor(MONSTER_YELLOW);
		pMonster->setTag(MonsterYellow);
		break;
	case 7:
	case 8:
	case 9:
		pMonster->setMonsterByType(MonsterBlue);
		pMonster->setScore(MONSTER_BLUE_SCORE);
		pMonster->setColor(MONSTER_BLUE);
		pMonster->setTag(MonsterBlue);
		break;
	case 10:
	case 11:
		pMonster->setMonsterByType(MonsterPurple);
		pMonster->setScore(MONSTER_PURPLE_SCORE);
		pMonster->setColor(MONSTER_PURPLE);
		pMonster->setTag(MonsterPurple);
		break;
	case 12:
	case 13:
		pMonster->setMonsterByType(MonsterGreen);
		pMonster->setScore(MONSTER_GREEN_SCORE);
		pMonster->setColor(MONSTER_GREEN);
		pMonster->setTag(MonsterGreen);
		break;
	case 14:
	case 15:
		pMonster->setMonsterByType(MonsterOrange);
		pMonster->setScore(MONSTER_ORANGE_SCORE);
		pMonster->setColor(MONSTER_ORANGE);
		pMonster->setTag(MonsterOrange);
		break;
	case 16:
		pMonster->setMonsterByType(MonsterBlack);
		pMonster->setScore(MONSTER_BLACK_SCORE);
		pMonster->setColor(MONSTER_BLACK);
		pMonster->setTag(MonsterBlack);
		break;
	default:
		break;
	}
	/*if (pMonster->getTag() == MonsterBlack) {
		char buff[20];
		Animation *panimation = Animation::create();
		panimation->setDelayPerUnit(3);
		for (int id = 0; id < 37; id++) {
			sprintf(buff, "black0000%d.png", id);
			panimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(buff));
		}
		pMonster->pMonsterSprite->runAction(RepeatForever::create(Animate::create(panimation)));
	}*/
	this->addChild(pMonster);
	vecMonster.pushBack(pMonster);
	auto actionMove = MoveTo::create(actionTime, Point(pMonster->getPositionX(), 200));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(MonsterLayer::removeMonster, this));
	Sequence *sq = Sequence::create(actionMove, actionDone, NULL);
	pMonster->runAction(sq);
}

//移除怪兽
void MonsterLayer::removeMonster(Node* pNode) {
	//for (int i = 0; i < monsterLayer->vecMonster.size(); i++) {
		//auto monster = monsterLayer->vecMonster.at(i);

	Monster *sp = (Monster *)pNode;
	if (sp->getPositionY() < 205) {
		sp->hit = true;
		switch (sp->getTag()){
		case MonsterRed:
		case MonsterYellow:
		case MonsterBlue:
			if (HelloWorld::unStoppable == true) {
				break;
			}
			else {
				HelloWorld::life -= sp->getScore();
				//Vibrator::Vibrate(50);
			}
			break;
		case MonsterPurple:
		case MonsterOrange:
		case MonsterGreen:
			if (HelloWorld::unStoppable == true) {
				break;
			}
			else {
				HelloWorld::life -= sp->getScore();
			}
			break;
		case MonsterBlack:
			if (HelloWorld::unStoppable == true) {
				break;
			}
			else {
				HelloWorld::life -= sp->getScore();
			}
			break;
		default:
			break;
		}
	}

	if (sp != NULL) {
		if (sp->hit == true) {
			this->removeChild(sp, true);
			vecMonster.eraseObject(sp);
			if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
				SimpleAudioEngine::getInstance()->playEffect("sound/dead.wav");
			}
		}

	}
}

void MonsterLayer::update(float t) {
	
}

void MonsterLayer::control(float t) {

	//积分模式下的控制条件
	if (HelloWorld::mode == 1) {
		if (actionTime > 3) {
			actionTime -= 0.01;
		}
		if (addTime > 0.55) {
			addTime -= 0.025;
		}
	}
	else if (HelloWorld::mode == 2) {
		if (actionTime > 3.5) {
			actionTime -= 0.01;
		}
		if (addTime > 0.6) {
			addTime -= 0.06;
		}
	}
	else if (HelloWorld::mode == 3) {
		if (actionTime > 2.5) {
			actionTime -= 0.01;
		}
		if (addTime > 0.55) {
			addTime -= 0.04;
		}
	}
	this->schedule(schedule_selector(MonsterLayer::addMonster), addTime);
}


void MonsterLayer::blowupMonster(Monster* pMonsterSprite) {
	/*Animation *pAnimation = NULL;
	Sprite *pmsprite = NULL;
	char *buff = NULL;
	if (Enemy1 == pMonsterSprite->getTag()) {
		buff = "a_001.png";
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy1Blowup");
		setScore(ENEMY1_SCORE);
	}
	else if (Enemy2 == pMonsterSprite->getTag()) {
		buff = "b_001.png";
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy2Blowup");
		setScore(ENEMY2_SCORE);
	}
	else if (Enemy3 == pMonsterSprite->getTag()) {
		buff = "d_00001.png";
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy3Blowup");
		setScore(ENEMY3_SCORE);
	}
	else {
		return;
	}
	pmsprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(buff));

	Point newPos = pEnemySprite->getcurPoint();
	Animate *pAnimate = Animate::create(pAnimation);
	pmsprite->setPosition(newPos);
	this->addChild(pmsprite);

	CallFuncN* mactiondone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::f_removemyAnimation, this, pmsprite));
	auto seq = Sequence::create(pAnimate, mactiondone, NULL);
	pmsprite->runAction(seq);
	removeEnemy(pEnemySprite);
	updateScore(m_score);*/
}
//移除动画
void MonsterLayer::removeAnimation(string s, Monster *monster) {
	monster->stopAllActions();
	monster->pMonsterSprite->stopAllActions();
	this->changeCondition(monster);
	char buff[30];
	string x;
	Animation *panimation = Animation::create();
	panimation->setDelayPerUnit(0.03f);
	for (int id = 1; id <= 42; id++) {
		if (id < 10) {
			sprintf(buff, "0000%d.png", id);
		}
		else {
			sprintf(buff, "000%d.png", id);
		}
		x = s + buff;
		panimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(x));
	}
	auto sprite = Sprite::create();
	Action * act = Sequence::create(
		Animate::create(panimation),
		CCCallFuncN::create(sprite, callfuncN_selector(MonsterLayer::killMe)),
		NULL);
	this->addChild(sprite);
	sprite->setPosition(Point(monster->getPositionX(), monster->getPositionY()));
	sprite->runAction(act);
	//auto actionDone = CallFuncN::create(CC_CALLBACK_1(MonsterLayer::changeCondition, this));
	//Sequence *sq = Sequence::create((Animate::create(panimation)), actionDone, NULL);
	//monster->pMonsterSprite->runAction(Animate::create(panimation));
	
	//this->schedule(schedule_selector(MonsterLayer::updateOnce), 1.2f);
	//this->schedule(schedule_selector(MonsterLayer::removeMonster), 0.0f, kRepeatForever, 0);
}

//删除当前节点并释放
void MonsterLayer::killMe(Node * pSender) {
	pSender->removeFromParentAndCleanup(true);
}


void MonsterLayer::changeCondition(Monster *monster) {
	monster->hit = true;
}

/*void MonsterLayer::updateOnce(float t) {
	for (int i = 0; i < this->vecMonster.size(); i++) {
		auto monster = this->vecMonster.at(i);
		if (monster->hit == true) {
			removeMonster(monster);
			i--;
			break;
		}
	}
}*/

