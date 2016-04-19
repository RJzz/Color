#include "BallLayer.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
/*Vector<Ball*> * BallLayer::allRed = new Vector<Ball*>();
Vector<Ball*> * BallLayer::allBlack = new Vector<Ball*>();
Vector<Ball*> * BallLayer::allBlue = new Vector<Ball*>();
Vector<Ball*> * BallLayer::allYellow = new Vector<Ball*>();
Vector<Ball*> * BallLayer::allOrange = new Vector<Ball*>();
Vector<Ball*> * BallLayer::allPurple = new Vector<Ball*>();
Vector<Ball*> * BallLayer::all = new Vector<Ball*>();*/
Vector<Ball*> * BallLayer::balls = new Vector<Ball*>();

Vector<Ball*> * BallLayer::getBalls(){
	return BallLayer::balls;
}

//��ʼ��
bool BallLayer::init() {
	if (!Layer::init()) {
		return false;
	}	
	addBall(BallRed);
	addBall(BallYellow);
	addBall(BallBlue);
	this->schedule(schedule_selector(BallLayer::minusTime), 0.01);
	this->scheduleUpdate();
	return true;
}

//�ںϳ�����
void BallLayer::mixBall(Ball *ball, string s) {
	char a[30];
	string buff;
	Animation *panimation = Animation::create();
	panimation->setRestoreOriginalFrame(true);	//ִ��֮�󷵻�ԭ����״̬
	panimation->setDelayPerUnit(0.01f);			//ִ�е�ʱ��
	for (int id = 1; id <= 21; id++) {
		sprintf(a, "%d", id);
		buff = s + "(" + a + ").png"; 
		panimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(buff));
	}
	ball->runAction(Animate::create(panimation));

}

//С����ײ���
void BallLayer::minusTime(float t) {
	for (int i = 0; i < balls->size(); i++) {
		auto ball = balls->at(i);
		if (ball->isMoved == true) {
			ball->time -= 0.01;
		}
	}
}
//���С��
void BallLayer::addBall(BallType type) {
	Ball* ball = nullptr;
	switch (type) {
	case BallRed:
		ball = RedBall::create();
		this->addChild(ball);
		balls->pushBack(ball);
		//allRed->pushBack(ball);
		break;
	case BallYellow:
		ball = YellowBall::create();
		this->addChild(ball);
		balls->pushBack(ball);
		//allYellow->pushBack(ball);
		break;
	case BallBlue:
		ball = BlueBall::create();
		this->addChild(ball);
		balls->pushBack(ball);
		//allBlue->pushBack(ball);
		break;
	default:
		break;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		return this->onTouchBegan(touch, event);
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event) {
		return this->onTouchMoved(touch, event);
	};
	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		return this->onTouchEnded(touch, event);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, ball);
}
void BallLayer::update(float t) {
	
	/*for (auto ball : allBall) {

	}*/
}

bool BallLayer::onTouchBegan(Touch *touch, Event *pEvent) {
	auto target = static_cast<Ball *>(pEvent->getCurrentTarget());		//��ȡ��ǰ�Ĵ���Ŀ��
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());//����������ϵת��Ϊ��������ϵ�����½�Ϊԭ�㣩
	Size s = target->getContentSize();//��ȡ������ı��ߴ��С
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode)) {
		log("touch");
		/*float x = target->getPositionX() + 35;
		float y = target->getPositionY();
		moveBeganX = x;
		moveBeganY = y;*/
		log(" ");
		log(locationInNode.x);
		return true;
	}
	return false;
}

//�����ƶ�,С���ں�
void BallLayer::onTouchMoved(Touch *touch, Event* pEvent) {
	auto target = static_cast<Ball *>(pEvent->getCurrentTarget());
	//�����ǰ������С��û��������ù������Ŵ������ƶ�
	if (target->isShoot == false) {
		target->setPosition(target->getPosition() + touch->getDelta());
		target->isMoved = true;
		//�õ�ǰ�Ĵ���Ŀ�����ڲ�����Ϸ�
		target->setZOrder(100);
		for (int i = 0; i < balls->size(); i++) {
			Ball* nowBall = balls->at(i);
			//����С��û�б����ʱ������ײ���
			if (target->getColor() != nowBall->getColor()) {
				if (nowBall->isShoot == false) {
					float x = target->getPositionX() - nowBall->getPositionX();
					float y = target->getPositionY() - nowBall->getPositionY();
					if (sqrtf(x * x + y * y) < 50){
						if ((nowBall->getColor() == RED_BALL && target->getColor() == YEIIOW_BALL) || (target->getColor() == RED_BALL && nowBall->getColor() == YEIIOW_BALL)) {
							target->setColor(ORANGE_BALL);
							target->setTag(BallOrange);
							//���¿�ʼ���㴥���ƶ���ʱ��
							
							target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("orangeBall.png"));
							mixBall(target, "orange100000");
							target->time = 1.5;

							if (nowBall->getColor() == YEIIOW_BALL) {
								target->moveBeganX = 140;
								target->moveBeganY = 60;
								//allYellow->eraseObject(nowBall);
								//allRed->eraseObject(target);
							}
							else if (nowBall->getColor() == RED_BALL) {
								target->moveBeganX = 230;
								target->moveBeganY = 30;
								//allRed->eraseObject(nowBall);
								//allYellow->eraseObject(target);
							}
							nowBall->removeFromParent();
							//allOrange->pushBack(target);
							balls->eraseObject(nowBall);
							log("cc");
							i--;
							addBall(BallYellow);
							addBall(BallRed);
							//Ŀ���Ѿ��ı���״̬
							target->isChange = true;
						
				
							
						}
						//�� + �� = ��
						else if ((nowBall->getColor() == BLUE_BALL && target->getColor() == YEIIOW_BALL) || (target->getColor() == BLUE_BALL && nowBall->getColor() == YEIIOW_BALL)) {
							target->setColor(GREEN_BALL);
							target->setTag(BallGreen);
							target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("greenBall.png"));
							target->setAnchorPoint(Vec2(0.5, 0.3));
							mixBall(target, "green100000 ");
							if (nowBall->getColor() == BLUE_BALL){
								target->moveBeganX = 330;
								target->moveBeganY = 52;
								//allBlue->eraseObject(nowBall);
								//allYellow->eraseObject(target);
							}
							else if (nowBall->getColor() == YEIIOW_BALL) {
								target->moveBeganX = 140;
								target->moveBeganY = 52;
								//allYellow->eraseObject(nowBall);
								//allBlue->eraseObject(target);
							}
							nowBall->removeFromParent();
							balls->eraseObject(nowBall);
							//all->pushBack(target);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            							nowBall->removeFromParent();
							i--;
							addBall(BallYellow);
							addBall(BallBlue);
							target->isChange = true;
							target->time = 1.5;
						}
						//�� + �� = ��
						else if (nowBall->getColor() == RED_BALL && target->getColor() == BLUE_BALL || target->getColor() == RED_BALL && nowBall->getColor() == BLUE_BALL) {
							target->setColor(PURPLE_BALL);
							target->setTag(BallPurple);
							target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("purpleBall.png"));
							target->setAnchorPoint(Vec2(0.5, 0.3));
							mixBall(target, "purple100000");
							if (nowBall->getColor() == RED_BALL) {
								target->moveBeganX = 240;
								target->moveBeganY = 30;
								//allRed->eraseObject(nowBall);
								//allBlue->eraseObject(target);
							}
							else if (nowBall->getColor() == BLUE_BALL) {
								target->moveBeganX = 330;
								target->moveBeganY = 52;
								//allBlue->eraseObject(nowBall);
								//allRed->eraseObject(target);
							}
							nowBall->removeFromParent();
							balls->eraseObject(nowBall);
							//allPurple->pushBack(target);
							
							i--;
							addBall(BallBlue);
							addBall(BallRed);
							target->isChange = true;
							target->time = 1.5;
						}
						//�� + �� = ��
						else if (target->getColor() == ORANGE_BALL && nowBall->getColor() == BLUE_BALL || nowBall->getColor() == ORANGE_BALL && target->getColor() == BLUE_BALL) {
							target->setColor(BLACK_BALL);
							target->setTag(BallBlack);
							target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blackBall.png"));
							mixBall(target, "black100000");
							if (nowBall->getColor() == ORANGE_BALL) {
								//target->moveBeganX = allOrange->at(0)->getPositionX();
								//target->moveBeganY = allOrange->at(0)->getPositionY();
								//allBlue->eraseObject(target);
								//allOrange->eraseObject(nowBall);
							}
							else if (nowBall->getColor() == BLUE_BALL) {
								target->moveBeganX = 336;
								target->moveBeganY = 52;
								//allOrange->eraseObject(target);
								//allBlue->eraseObject(nowBall);
							}
							nowBall->removeFromParent();
							balls->eraseObject(nowBall);
							//allBlack->pushBack(target);
							
							i--;
							addBall(BallBlue);
							target->isChange = true;
							target->time = 1.5;
						}
						//�� + �� = ��
						else if (target->getColor() == PURPLE_BALL && nowBall->getColor() == YEIIOW_BALL || target->getColor() == YEIIOW_BALL && nowBall->getColor() == PURPLE_BALL) {
							target->setColor(BLACK_BALL);
							target->setTag(BallBlack);
							target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blackBall.png"));
							mixBall(target, "black100000");
							if (nowBall->getColor() == PURPLE_BALL) {
								//allYellow->eraseObject(target);
								//allPurple->eraseObject(nowBall);
							}
							else if (nowBall->getColor() == YEIIOW_BALL) {
								target->moveBeganX = 135;
								target->moveBeganY = 52;
								//allPurple->eraseObject(target);
								//allYellow->eraseObject(nowBall);
							}
							nowBall->removeFromParent();
							balls->eraseObject(nowBall);
							//allBlack->pushBack(target);
							
							i--;
							addBall(BallYellow);
							target->isChange = true;
							target->time = 1.5;
						}
						//�� + �� = ��
						else if (target->getColor() == GREEN_BALL && nowBall->getColor() == RED_BALL || target->getColor() == RED_BALL && nowBall->getColor() == GREEN_BALL) {
							target->setColor(BLACK_BALL);
							target->setTag(BallBlack);
							target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blackBall.png"));
							mixBall(target, "black100000");
							if (nowBall->getColor() == GREEN_BALL) {
								//allRed->eraseObject(target);
								//allGreen->eraseObject(nowBall);
							}
							else if (nowBall->getColor() == RED_BALL) {
								target->moveBeganX = 240;
								target->moveBeganY = 30;
								//allGreen->eraseObject(target);
								//allRed->eraseObject(nowBall);
							}
							nowBall->removeFromParent();
							balls->eraseObject(nowBall);
							
							//allBlack->pushBack(target);
							i--;
							addBall(BallRed);
							target->isChange = true;
							target->time = 1.5;
						}
						//�ı�moveBegan��ֵ
						/*float x = target->getPositionX();
						float y = target->getPositionY();
						moveBeganX = x;
						moveBeganY = y;*/

					}
				}
			}
		}
	}
}

//����������С���������ص�ԭ����λ��
void BallLayer::onTouchEnded(Touch* touch, Event* event) {
	//��ȡ��ǰ�Ĵ���Ŀ��
	auto target = static_cast<Ball *>(event->getCurrentTarget());	
	Point xa = touch->getLocation();
	target->moveEndedX = target->getPositionX();
	target->moveEndedY = target->getPositionY();
	//��ǰС����ƶ�״̬�ı�
	target->isMoved = false;
	//��������ƶ���ʱ��С��0.3�룬��Ϊ�������Ҫ�������
	if (target->time <= 1.5 && target->time > 1.2 && target->isShoot == false && (abs(target->getPositionX() - target->moveBeganX) > 0.25) && (abs(target->getPositionY() - target->moveBeganY) > 0.25))  {
		target->isShoot = true;
		float x = (target->moveEndedX - target->moveBeganX) * 1000;
		float y = (target->moveEndedY - target->moveBeganY) * 1000;
		float time = 120 - target->time * 20;
		//��С�����Լ��Ļ������Ƽ������
		auto actionMove = MoveBy::create(time, Point(x, y));
		Sequence *sq = Sequence::create(actionMove, NULL);
		target->runAction(sq);
		//����������ԭɫ��Ļ���������������С��
		switch (target->getTag()) {
		case BallRed:
			addBall(BallRed);
			break;
		case BallBlue:
			addBall(BallBlue);
			break;
		case BallYellow:
			addBall(BallYellow);
			break;
		default:
			break;
		}
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/shoot.wav");
		}
	}
	//���С���û���������û�н�����ɫ�ںϣ�����ԭ����ԭɫ����С��Żس�ʼλ��
	if (target->isShoot == false && target->isChange == false) {
		switch (target->getTag()) {   
		case BallRed:
			target->setPosition(238, 30);
			break;
		case BallBlue:
			target->setPosition(338, 55);
			break;
		case BallYellow:
			target->setPosition(134, 55);
			break;
		default:
			break;
		}
		target->time = 1.5;
	}
	//�����Ϊ���֮ǰԽ���ˣ��������Ѿ��ں��ˣ��Ǿ��ڷſ��ֵ�ʱ��������ʧ����Ϊ���������ȥ����ޣ�������ֱ������С��ײ����
	else if (target->isChange == true && target->time <= 1.2) {
		this->removeBall(target);
		balls->eraseObject(target);
		/*switch (target->getTag()) {
		case BallRed:
			allRed->eraseObject(target);
			break;
		case BallBlue:
			allBlue->eraseObject(target);
			break;
		case BallYellow:
			allYellow->eraseObject(target);
			break;
		case BallPurple:
			allPurple->eraseObject(target);
			break;
		case BallOrange:
			allOrange->eraseObject(target);
			break;
		case BallGreen:
			allGreen->eraseObject(target);
			break;
		case BallBlack:
			allBlack->eraseObject(target);
			break;
		default:
			break;
		}*/
	}
}
void BallLayer::removeBall(Ball* ball) {
	Ball* b = (Ball *)ball;
	if (ball != NULL) {
		this->removeChild(b, true);
		balls->eraseObject(b);
	}
}


/*Ball* BallLayer::addEvent() {

}*/
void update(float t) {
	for (int i = 0; i < BallLayer::getBalls()->size(); i++) {
		auto ball = BallLayer::getBalls()->at(i);
		if (ball->getPositionY() > 240) {
			ball->isShoot = true;
		}
		if (ball->getPositionX() < 0 || ball->getPositionX() > 480 || ball->getPositionY() < 0 || ball->getPositionY() > 839) {
			ball->removeFromParent();
			BallLayer::getBalls()->eraseObject(ball);
		}
	}
}




