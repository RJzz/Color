#include "Tools.h"

//���ݵ��ߵ�������������ͬ�Ĺ���
void Tools::setToolsType(ToolsType moType) {
	switch (moType) {
	case Clean:
		pTools = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("clean.png"));
		break;
	case Strong:
		pTools = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("strong.png"));
		break;
	case DoubleScore:
		pTools = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("double.png"));
		break;
	case Ice:
		pTools = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ice.png"));
		break;
	case Life:
		pTools = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("life.png"));
		break;
	default:
		return;
		break;
	}
	this->addChild(pTools);
	Size winSize = Director::getInstance()->getWinSize();
	Size monsterSize = pTools->getContentSize();
	//���ù���������ֵ�λ��
	int minX = monsterSize.width / 2;
	int maxX = winSize.width - monsterSize.width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;
	this->setPosition(Point(actualX, winSize.height + monsterSize.height / 2));
}

//ȡ�ô����Ĺ��޾���
Sprite * Tools::getSprite() {
	return pTools;
}

//��ȡ�������ڵ�λ��
Point Tools::getcurPoint() {
	return this->getPosition();
}

//��ȡ�������
Rect Tools::getBoundingBox() {
	Rect rect = pTools->boundingBox();
	Point pos = this->convertToWorldSpace(rect.origin);
	Rect monsterRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return monsterRect;
}


