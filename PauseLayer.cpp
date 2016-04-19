#include "PauseLayer.h"
#include "GameSceneScore.h"
#include "GameSceneTime.h"
#include "GameSceneTools.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool PauseLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	//����Ŀǰ��һ�����İ취����menu�̲���һ���MenuItem����¼�
	//auto bg = Sprite::create("back.png");
	auto bg = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_1(PauseLayer::menuCallBack, this));
	bg->setOpacity(100);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(0, 0);

	


	//һЩ��ť
	//������Ϸ
	auto continueItem = MenuItemImage::create("begin.png", "begin.png", CC_CALLBACK_1(PauseLayer::menuCallBack, this));

	//�ص���ʼҳ��
	auto homeItem = MenuItemImage::create("home.png", "home.png", CC_CALLBACK_1(PauseLayer::menuCallBack, this));
	//���¿�ʼ
	auto restartItem = MenuItemImage::create("again.png", "again.png", CC_CALLBACK_1(PauseLayer::menuCallBack, this));
	//���ý���
	auto settingItem = MenuItemImage::create("set.png", "set.png", CC_CALLBACK_1(PauseLayer::menuCallBack, this));


	continueItem->setTag(10);
	homeItem->setTag(11);
	restartItem->setTag(12);
	settingItem->setTag(13);


	continueItem->setPosition(240, 425);
	homeItem->setPosition(162, 310);
	restartItem->setPosition(245, 297);
	settingItem->setPosition(326, 310);


	auto menu = Menu::create(bg, continueItem, homeItem, restartItem, settingItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;

}

void PauseLayer::menuCallBack(Ref* pSender) {
	MenuItem *nowItem = (MenuItem *)pSender;
	switch (nowItem->getTag()) {
	case 10:
		//����
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		log("������Ϸ");
		Director::getInstance()->resume();
		//�ӵ�ǰ�������Ƴ���ͣ��
		this->removeFromParent();
		//Director::getInstance()->getRunningScene()->removeChild(GameSceneScore::pauseLayer);
		break;
		//���ػ�ӭҳ��
	case 11:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		log("���ػ�ӭ����");
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, HelloWorld::createScene()));
		break;
		//���¿�ʼ��Ϸ
	case 12:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		//����ģʽ
		if (HelloWorld::mode == 1) {

			Director::getInstance()->replaceScene(GameSceneScore::createScene());
		}
		//ʱ��ģʽ
		else if (HelloWorld::mode == 2) {

			Director::getInstance()->replaceScene(GameSceneTime::createScene());
		}
		//�ֻ�ģʽ
		else if (HelloWorld::mode == 3) {
			Director::getInstance()->replaceScene(GameSceneTools::createScene());
		}
		Director::getInstance()->resume();
		break;
	case 13:
		if (UserDefault::getInstance()->getBoolForKey(SOUND)) {
			SimpleAudioEngine::getInstance()->playEffect("sound/select.wav");
		}
		settingLayer = SettingLayer::create();
		this->addChild(settingLayer, 3);
		break;
	default:
		break;
	}
}
