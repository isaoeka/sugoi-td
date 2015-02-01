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
    mSpeed = arc4random() % 3 + 1;
    log("[sugoienemy] create!");
    log("[SugoiEnemy] speed : %d", mSpeed);

    this->scheduleUpdate();
    // do things here like setTag(), setPosition(), any custom logic.

    // pos
    Size winSize = Director::getInstance()->getWinSize(); //—画面サイズを取得
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin(); //—端末左下の座標を取得
    Vec2 cs = this->getContentSize();

    int randomNum = arc4random() % (int)visibleSize.height;
    log("[SugoiEnemy] pos height randum : %d", randomNum);
    this->setPosition(Vec2(visibleSize.width + cs.x, randomNum));

    // tag
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

// 実装
// this->scheduleUpdate()を実行するとフレーム単位で以下が自動的に呼ばれるようになる
void SugoiEnemy::update(float frame)
{
    Vec2 pos = this->getPosition();
    pos.x = pos.x - mSpeed;
    this->setPosition(Vec2(
        pos.x,
        pos.y));

    //    log("[SugoiEnemy] frame is %f", frame);
    //    log("[SugoiEnemy] pos %f:%f", pos.x, pos.y);
}
