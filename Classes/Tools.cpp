#include "Tools.h"

//根据道具的类型来创建不同的怪兽
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
	//设置怪物随机出现的位置
	int minX = monsterSize.width / 2;
	int maxX = winSize.width - monsterSize.width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;
	this->setPosition(Point(actualX, winSize.height + monsterSize.height / 2));
}

//取得创建的怪兽精灵
Sprite * Tools::getSprite() {
	return pTools;
}

//获取怪兽现在的位置
Point Tools::getcurPoint() {
	return this->getPosition();
}

//获取外包矩形
Rect Tools::getBoundingBox() {
	Rect rect = pTools->boundingBox();
	Point pos = this->convertToWorldSpace(rect.origin);
	Rect monsterRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return monsterRect;
}


