#include "MainGameScene.h"
#include "SugoiEnemy.h"

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

    auto label = Label::createWithTTF("ゲーム画面", "fonts/FGModernGothic.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    std::vector<SugoiEnemy*> enemys;
    //
    while (enemys.size() < 30) {
        enemys.push_back(SugoiEnemy::create());
    }

    for (SugoiEnemy* itl : enemys) {
        this->addChild(itl, 0);
    }

    //    auto actionManager = Director::getInstance()->getActionManager();
    scheduleOnce(schedule_selector(MainGameScene::timeUp), 15.0f);

    return true;
}

//-------------------------------------------------------------------
#pragma mark -  callback
//-------------------------------------------------------------------

void MainGameScene::gameStart(float frame)
{
}

void MainGameScene::timeUp(float frame)
{
    log("time up !!");
}

void MainGameScene::gameOver(float frame)
{
}
