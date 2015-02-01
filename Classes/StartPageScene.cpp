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

    // Set an image to a texture, set the param "repeat"
    Texture2D* bgTexture = Director::getInstance()->getTextureCache()->addImage("res/bg/bg.png");
    const Texture2D::TexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
    bgTexture->setTexParameters(tp);

    // use the texture as Sprite
    Sprite* background = Sprite::createWithTexture(bgTexture, Rect(0, 0, visibleSize.width, visibleSize.height));
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background, 1);

    auto closeItem = MenuItemImage::create(
        "res/ui/btn_start.png",
        "res/ui/btn_start_on.png",
        CC_CALLBACK_1(StartPageScene::myCallback, this));

    closeItem->setPosition(Vec2(visibleSize.width / 2, origin.y + closeItem->getContentSize().height / 2 + 50));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("すごいTD", "fonts/FGModernGothic.ttf", 250);
    label->setColor(Color3B(76, 76, 76));
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
