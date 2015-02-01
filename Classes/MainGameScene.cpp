#include "MainGameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define SOUND_EFFECT "res/sound/powerdown07.mp3"
#define ENEMY_COUNT 20

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

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Set an image to a texture, set the param "repeat"
    Texture2D* bgTexture = Director::getInstance()->getTextureCache()->addImage("res/bg/bg.png");
    const Texture2D::TexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
    bgTexture->setTexParameters(tp);
    // use the texture as Sprite
    Sprite* background = Sprite::createWithTexture(bgTexture, Rect(0, 0, visibleSize.width, visibleSize.height));
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setGlobalZOrder(0);
    this->addChild(background, 1);

    float playtime = 15.0f;
    this->gameSetting(playtime);
    this->gameStart(playtime);

    this->initJijin();

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

void MainGameScene::initJijin()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Set an image to a texture, set the param "repeat"
    Texture2D* bgTexture = Director::getInstance()->getTextureCache()->addImage("res/bg/jijin.png");
    const Texture2D::TexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
    bgTexture->setTexParameters(tp);
    // use the texture as Sprite
    Sprite* background = Sprite::createWithTexture(bgTexture, Rect(0, 0, 200, visibleSize.height));
    background->setPosition(Vec2(0, visibleSize.height / 2));

    background->setGlobalZOrder(0);
    this->addChild(background, 1);

    auto label = Label::createWithTTF("す\nご\nい\nじ\nじ\nん", "fonts/FGModernGothic.ttf", 65);
    label->setColor(Color3B(76, 76, 76));
    label->setPosition(Vec2(150, visibleSize.height / 2));
    background->addChild(label, 1);
}

void MainGameScene::initScoreCounter(float frame)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto scoreString = String::createWithFormat("TIME : %.02f", frame);
    mTimeScoreLabel = Label::createWithTTF(scoreString->getCString(), "fonts/FGModernGothic.ttf", 40);
    mTimeScoreLabel->setPosition(Vec2(100 + origin.x + visibleSize.width / 2, origin.y + visibleSize.height - mTimeScoreLabel->getContentSize().height));
    mTimeScoreLabel->setGlobalZOrder(20);
    this->addChild(mTimeScoreLabel, 3);

    auto enemyString = String::createWithFormat("ENEMY : %d/%d", 0, ENEMY_COUNT);
    mEnemyScoreLabel = Label::createWithTTF(enemyString->getCString(), "fonts/FGModernGothic.ttf", 40);
    mEnemyScoreLabel->setPosition(Vec2(200, origin.y + visibleSize.height - mEnemyScoreLabel->getContentSize().height));
    mEnemyScoreLabel->setGlobalZOrder(20);
    this->addChild(mEnemyScoreLabel, 30);

    this->schedule(schedule_selector(MainGameScene::updateScore));
    this->schedule(schedule_selector(MainGameScene::judgeUpdate));
}

//-------------------------------------------------------------------
#pragma mark -  callback
//-------------------------------------------------------------------

void MainGameScene::gameSetting(float frame)
{
    // Enemy
    while (mEnemys.size() < ENEMY_COUNT) {
        mEnemys.push_back(SugoiEnemy::create());
    }
}

void MainGameScene::gameStart(float frame)
{
    fg_playing = true;
    log("play !!");

    //    auto actionManager = Director::getInstance()->getActionManager();
    scheduleOnce(schedule_selector(MainGameScene::timeUp), frame);

    this->initScoreCounter((int)frame);

    for (SugoiEnemy* itl : mEnemys) {
        this->addChild(itl, 0);
    }
}

void MainGameScene::gameClear(float frame)
{
    this->unschedule(schedule_selector(MainGameScene::updateScore));
    this->unschedule(schedule_selector(MainGameScene::judgeUpdate));
    this->unscheduleUpdate();

    fg_playing = false;
    log("play Clear !!");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
        "res/enemy/1.png",
        "res/enemy/2.png",
        CC_CALLBACK_1(MainGameScene::myCallback, this));
    closeItem->setPosition(Vec2(visibleSize.width / 2, origin.y + closeItem->getContentSize().height / 2 + 50));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("CLEAR!!", "fonts/FGModernGothic.ttf", 100);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    label->setGlobalZOrder(100);
    this->addChild(label, 1);

    mEnemys.clear();
}

void MainGameScene::timeUp(float frame)
{
    log("time up !!");

    if (fg_playing) {
        SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT);

        auto label = Label::createWithTTF("TIMEUP!!", "fonts/FGModernGothic.ttf", 100);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        label->setGlobalZOrder(100);
        this->addChild(label, 1);

        for (SugoiEnemy* itl : mEnemys) {
            itl->timeUp();
        }
    }

    fg_timeup = true;
    fg_playing = false;
}

void MainGameScene::gameOver(float frame)
{
    fg_gameover = true;
    fg_playing = false;
    log("gema over !!");

    SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT);
    this->unschedule(schedule_selector(MainGameScene::updateScore));
    this->unschedule(schedule_selector(MainGameScene::judgeUpdate));
    this->unscheduleUpdate();

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

void MainGameScene::myCallback(Ref* pSender)
{
    this->removeAllChildren();

    this->gameSetting(1.1);
    this->gameStart(15.0);
}

//-------------------------------------------------------------------
#pragma mark -  update
//-------------------------------------------------------------------

void MainGameScene::judgeUpdate(float frame)
{
    int enemycount = 0;
    for (SugoiEnemy* itl : mEnemys) {
        Vec2 vec = itl->getPosition();
        if (vec.x < 0 && fg_playing && itl->isVisible()) {
            gameOver(1.0);
        }
        else {
            enemycount += !itl->isVisible() ? 1 : 0;
            if (enemycount >= ENEMY_COUNT) {
                gameClear(1.0);
            }
        }
    }
    auto enemyString = String::createWithFormat("ENEMY : %d/%d", enemycount, ENEMY_COUNT);
    mEnemyScoreLabel->setString(enemyString->getCString());
    enemycount = 0;
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
        mTimeScoreLabel->setString(scoreString->getCString());
    }
}
