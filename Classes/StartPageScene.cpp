#include "StartPageScene.h"

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
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "enemy/1.png",
        "enemy/2.png",
        CC_CALLBACK_1(StartPageScene::myCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
        origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    return true;
}

//-------------------------------------------------------------------
#pragma mark -  callback
//-------------------------------------------------------------------

void StartPageScene::myCallback(Ref* pSender)
{
    log("タップされました。");
}

void StartPageScene::gameStart(int difficulty)
{
    auto scene = StartPageScene::createScene();
    // 0.5秒かけてホワイトアウトしてタイトルに移動する
    TransitionFade* fade = TransitionFade::create(0.5f, scene, Color3B::WHITE);
    Director::getInstance()->replaceScene(fade);
}
