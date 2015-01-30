#include "MainScene.h"
#include "RollingScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bkgSprite = Sprite::create("UI/startscreen.jpg");
    this->addChild(bkgSprite);
    bkgSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    auto startSpriteNormal = Sprite::create("UI/start.png");
    auto startSpriteSelected = Sprite::create("UI/start.png");
    auto rectSelected = startSpriteSelected->getTextureRect();
    startSpriteSelected->setScale(1.1f);
    startSpriteSelected->setColor(Color3B(255, 100, 100));
    startSpriteSelected->setPosition(Vec2(-rectSelected.getMaxX() * 0.05, -rectSelected.getMaxY() * 0.05));

    auto startButton = MenuItemSprite::create(startSpriteNormal, startSpriteSelected, CC_CALLBACK_1(MainScene::menuStartCallback, this));
    startButton->setPosition(visibleSize.width / 2, visibleSize.height / 4);
    auto menu = Menu::create(startButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto buttonEffect = Blink::create(3.0, 3);
    startButton->runAction(buttonEffect);

    return true;
}


void MainScene::menuStartCallback(Ref* pSender)
{
    auto rollingScene = RollingScene::createScene();
    auto rollingSceneAnimated = TransitionTurnOffTiles::create(0.5f, rollingScene);
    Director::getInstance()->replaceScene(rollingSceneAnimated);
}

void MainScene::onEnter()
{
    Layer::onEnter();
    this->setCascadeOpacityEnabled(true);
    auto effect = FadeIn::create(5.0f);
    this->runAction(effect);
}