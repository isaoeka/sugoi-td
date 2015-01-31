//
//  SugoiEnemy.cpp
//  sugoi-td
//
//  Created by Isao Kono on 2015/01/31.
//
//

#include "SugoiEnemy.h"

using namespace cocos2d;

SugoiEnemy::SugoiEnemy() {}

SugoiEnemy::~SugoiEnemy() {}

SugoiEnemy* SugoiEnemy::create()
{
    SugoiEnemy* pSprite = new SugoiEnemy();

    if (pSprite->initWithFile("enemy/4.png")) {
        pSprite->autorelease();

        pSprite->initOptions();

        pSprite->addEvents();

        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void SugoiEnemy::initOptions()
{
    // do things here like setTag(), setPosition(), any custom logic.
}

void SugoiEnemy::addEvents()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        
        if(rect.containsPoint(p))
        {
            return true; // to indicate that we have consumed it.
        }
        
        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        SugoiEnemy::touchEvent(touch);
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void SugoiEnemy::touchEvent(cocos2d::Touch* touch)
{
    // タップしたら消去
    this->removeFromParentAndCleanup(true);
}