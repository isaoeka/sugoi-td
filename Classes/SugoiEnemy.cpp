//
//  SugoiEnemy.cpp
//  sugoi-td
//
//  Created by Isao Kono on 2015/01/31.
//
//

#include "SugoiEnemy.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define SOUND_EFFECT "res/sound/coin05.mp3"

SugoiEnemy::SugoiEnemy()
{
}

SugoiEnemy::~SugoiEnemy() {}

SugoiEnemy* SugoiEnemy::create()
{
    SugoiEnemy* pSprite = new SugoiEnemy();

    if (pSprite->initWithFile("res/enemy/4.png")) {
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
    fg_playing = true;
    mSpeed = arc4random() % 3 + 1;
    mLifeCount = arc4random() % 4 + 1;
    log("[SugoiEnemy] speed : %d", mSpeed);
    log("[SugoiEnemy] life : %d", mLifeCount);
    initLifeCounter(mLifeCount);

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
    if (this->isVisible() && fg_playing) {
        mLifeCount--;
        updateLifeCounter(mLifeCount);
        if (0 >= mLifeCount) {
            this->sinu();
        }
    }
}

void SugoiEnemy::sinu()
{
    SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT);
    this->setVisible(false);
}

void SugoiEnemy::initLifeCounter(int life)
{
    auto lifetexturename = String::createWithFormat("res/enemy/%d.png", life);
    this->setTexture(lifetexturename->getCString());

    //    Size visibleSize = Director::getInstance()->getVisibleSize();
    //    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //    auto scoreString = String::createWithFormat("[%d]", life);
    //    mLifeLabel = Label::createWithTTF(scoreString->getCString(), "fonts/FGModernGothic.ttf", 30);
    //    mLifeLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    //    this->addChild(mLifeLabel, 3);
}

void SugoiEnemy::updateLifeCounter(int life)
{
    auto lifetexturename = String::createWithFormat("res/enemy/%d.png", life);
    this->setTexture(lifetexturename->getCString());
}

void SugoiEnemy::update(float frame)
{
    Vec2 pos = this->getPosition();
    pos.x = pos.x - mSpeed;
    this->setPosition(Vec2(
        pos.x,
        pos.y));
}

void SugoiEnemy::timeUp()
{
    this->unscheduleUpdate();
    fg_playing = false;
}