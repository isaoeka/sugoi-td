#include "MainGameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define SOUND_EFFECT "res/sound/powerdown07.mp3"

USING_NS_CC;

Scene* MainGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainGameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainGameScene::init()
{
    if (!Layer::init()) {
        return false;
    }

    float playtime = 15.0f;

    this->gameSetting(playtime);
    this->gameStart(playtime);

    return true;
}

void MainGameScene::initFlag()
{
    fg_playing = false;
    fg_gameover = false;
    fg_timeup = false;
}

std::map<std::string, bool> getFlags()
{
    std::map<std::string, bool> boolMap;

    return boolMap;
}

void MainGameScene::initTimeCounter(float frame)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto scoreString = String::createWithFormat("TIME : %.02f", frame);
    mScoreLabel = Label::createWithTTF(scoreString->getCString(), "fonts/FGModernGothic.ttf", 40);
    mScoreLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - mScoreLabel->getContentSize().height));
    this->addChild(mScoreLabel, 3);

    this->schedule(schedule_selector(MainGameScene::updateScore));
    this->schedule(schedule_selector(MainGameScene::judgeUpdate));
}

//-------------------------------------------------------------------
#pragma mark -  callback
//-------------------------------------------------------------------

void MainGameScene::gameSetting(float frame)
{
    // Enemy
    while (mEnemys.size() < 30) {
        mEnemys.push_back(SugoiEnemy::create());
    }
}

void MainGameScene::gameStart(float frame)
{
    fg_playing = true;
    log("play !!");

    //    auto actionManager = Director::getInstance()->getActionManager();
    scheduleOnce(schedule_selector(MainGameScene::timeUp), frame);

    this->initTimeCounter((int)frame);

    for (SugoiEnemy* itl : mEnemys) {
        this->addChild(itl, 0);
    }
}

void MainGameScene::timeUp(float frame)
{
    fg_timeup = true;
    fg_playing = false;
    log("time up !!");

    if (fg_playing) {
        SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT);

        auto label = Label::createWithTTF("TIMEUP!!", "fonts/FGModernGothic.ttf", 100);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        this->addChild(label, 1);

        for (SugoiEnemy* itl : mEnemys) {
            itl->timeUp();
        }
    }
}

void MainGameScene::gameOver(float frame)
{
    fg_gameover = true;
    fg_playing = false;
    log("gema over !!");

    SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT);

    auto label = Label::createWithTTF("GAMEOVER!!", "fonts/FGModernGothic.ttf", 100);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(label, 2);

    for (SugoiEnemy* itl : mEnemys) {
        itl->timeUp();
    }
}

std::vector<SugoiEnemy*> MainGameScene::getEnemys()
{
    return mEnemys;
}

//-------------------------------------------------------------------
#pragma mark -  update
//-------------------------------------------------------------------

void MainGameScene::judgeUpdate(float frame)
{
    for (SugoiEnemy* itl : mEnemys) {
        Vec2 vec = itl->getPosition();
        if (vec.x < 0 && fg_playing) {
            gameOver(1.0);
        }
    }
}

void MainGameScene::updateScore(float frame)
{
    static float time = 15.0f;
    if (time <= 0) {
        // スケジュールの停止
        this->unschedule(schedule_selector(MainGameScene::updateScore));
    }
    else {
        time = time - frame;
        auto scoreString = String::createWithFormat("TIME : %.02f", time);
        mScoreLabel->setString(scoreString->getCString());
    }
}
