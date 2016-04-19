#include "Monster.h"


//根据怪兽的类型来创建不同的怪兽
void Monster::setMonsterByType(MonsterType moType) {
	if (moType == MonsterRed) {
		pMonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("redMonster.png"));
		walk("red", 31);
	}
	else if (moType == MonsterBlue) {
		pMonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blueMonster.png"));
		walk("blue", 31);
	}
	else if (moType == MonsterYellow) {
		pMonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("yellowMonster.png"));
		walk("yellow", 31);
	}
	else if (moType == MonsterGreen) {
		pMonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("greenMonster.png"));
		walk("green", 41);
	}
	else if (moType == MonsterPurple) {
		pMonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("purpleMonster.png"));
		walk("purple", 40);
	}
	else if (moType == MonsterOrange) {
		pMonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("orangeMonster.png"));
		walk("orange", 41);
	}
	else if (moType == MonsterBlack) {
		pMonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blackMonster.png"));
		walk("black", 35);
	}
	this->addChild(pMonsterSprite);
	Size winSize = Director::getInstance()->getWinSize();
	Size monsterSize = pMonsterSprite->getContentSize();
	//设置怪物随机出现的位置
	int minX = monsterSize.width / 2;
	int maxX = winSize.width - monsterSize.width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;
	this->setPosition(Point(actualX, winSize.height + monsterSize.height / 2));
}

//取得创建的怪兽精灵
Sprite * Monster::getSprite() {
	return pMonsterSprite;
}

//获取怪兽现在的位置
Point Monster::getcurPoint() {
	return this->getPosition();
}

//获取外包矩形
Rect Monster::getBoundingBox() {
	Rect rect = pMonsterSprite->boundingBox();
	Point pos = this->convertToWorldSpace(rect.origin);
	Rect monsterRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return monsterRect;
}

//设置怪兽的分数
void Monster::setScore(int score) {
	this->score = score;
}

//获得怪兽的分数
int Monster::getScore() {
	return this->score;
}

//设置怪兽的颜色
void Monster::setColor(string color) {
	this->color = color;
}

//获得怪兽的颜色
string Monster::getColor() {
	return this->color;
}

//行走的动图
void Monster::moveAnimation(MonsterType moType) {
	switch (moType)  {
	case MonsterBlack:
		
		break;
	default:
		break;
	}
	
}

//行走动图
void Monster::walk(string s, int pictureN) {
	char buff[30];
	string x;
	Animation *panimation = Animation::create();
	panimation->setDelayPerUnit(0.04f);
	for (int id = 1; id <= pictureN; id++) {
		if (id < 10) {
			sprintf(buff, "-walk00000%d.png", id);
		}
		else {
			sprintf(buff, "-walk0000%d.png", id);
		}
		x = s + buff;
		panimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(x));
	}
	pMonsterSprite->runAction(RepeatForever::create(Animate::create(panimation)));
}

//重新开始行走
void Monster::resumeWalk(float t) {
	if (this->frozen == true) {
		this->frozen = false;

		this->pMonsterSprite->resumeSchedulerAndActions();
		if (this->getTag() == MonsterRed) {
			this->pMonsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("redMonster.png"));
			this->walk("red", 31);
		}
		else if (this->getTag() == MonsterBlue) {
			this->pMonsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blueMonster.png"));
			this->walk("blue", 31);
		}
		else if (this->getTag() == MonsterYellow) {
			this->pMonsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("yellowMonster.png"));
			this->walk("yellow", 31);
		}
		else if (this->getTag() == MonsterGreen) {
			this->pMonsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("greenMonster.png"));
			this->walk("green", 41);
		}
		else if (this->getTag() == MonsterPurple) {
			this->pMonsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("purpleMonster.png"));
			this->walk("purple", 40);
		}
		else if (this->getTag() == MonsterOrange) {
			this->pMonsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("orangeMonster.png"));
			this->walk("orange", 41);
		}
		else if (this->getTag() == MonsterBlack) {
			this->pMonsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blackMonster.png"));
			this->walk("black", 35);
		}
		this->resumeSchedulerAndActions();
	}

}

