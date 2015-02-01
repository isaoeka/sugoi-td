#include "StartPageScene.h"
#include "MainGameScene.h"

USING_NS_CC;

Scene* StartPageScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = StartPageScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartPageScene::init()
{
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
        "res/enemy/1.png",
        "res/enemy/2.png",
        CC_CALLBACK_1(StartPageScene::myCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
        origin.y + closeItem->getContentSize().height / 2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("スタートページ", "fonts/FGModernGothic.ttf", 24);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(label, 1);

    return true;
}

//-------------------------------------------------------------------
#pragma mark -  callback
//-------------------------------------------------------------------

void StartPageScene::myCallback(Ref* pSender)
{
    log("タップされました。");
    gameStart(1);
}

void StartPageScene::gameStart(int difficulty)
{
    auto scene = MainGameScene::createScene();
    // 0.5秒かけてホワイトアウトしてタイトルに移動する
    TransitionFade* fade = TransitionFade::create(0.5f, scene, Color3B::WHITE);
    Director::getInstance()->replaceScene(fade);
}
