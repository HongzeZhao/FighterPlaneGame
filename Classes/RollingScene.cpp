#include "RollingScene.h"
#include "MainScene.h"
#include "PlayerPlane.h"
#include "EnemyPlane.h"

USING_NS_CC;

Scene* RollingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = RollingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RollingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    // rolling background
    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();

    // rolling background
    const float rollingFrequency = 20.0f;
    auto bkgTexture = director->getTextureCache()->addImage("background.jpg");
    auto textureSize = bkgTexture->getContentSize();
    auto rollingBkg0 = Sprite::createWithTexture(bkgTexture);
    auto rollingAction0 = RepeatForever::create(Sequence::create(
        Place::create(Vec2(textureSize.width / 2, textureSize.height)),
        MoveTo::create(rollingFrequency, Vec2(textureSize.width / 2, 0)),
        NULL
        ));
    this->addChild(rollingBkg0, -1);
    rollingBkg0->runAction(rollingAction0);

    auto rollingBkg1 = Sprite::createWithTexture(bkgTexture);
    auto rollingAction1 = RepeatForever::create(Sequence::create(
        Place::create(Vec2(textureSize.width / 2, 0)),
        MoveTo::create(rollingFrequency, Vec2(textureSize.width / 2, -textureSize.height)),
        NULL
        ));
    this->addChild(rollingBkg1, -1);
    rollingBkg1->runAction(rollingAction1);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("entities.plist", "entities.png");

    Plane::onSetResourcesWithName = [](Plane::ResourceDescriptor &descriptor, const std::string &name)
    {
        if (name == "player")
        {
            descriptor.frameNameHit = "fighter_hurt.png";
            descriptor.frameNameInvincible = "invincible.png";
            descriptor.frameNameNormal = "fighter1.png";
            descriptor.frameNameShadow = "fighter_shadow.png";

            Vector<SpriteFrame*> figherFrames;
            figherFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fighter1.png"));
            figherFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("fighter2.png"));
            auto fighterAnimation = Animation::createWithSpriteFrames(figherFrames, 0.2f);

            descriptor.actionNormal = RepeatForever::create(Animate::create(fighterAnimation));
        }

#define ENEMY_PLANE_NS(_name_) descriptor.frameNameNormal = _name_".png"; descriptor.frameNameShadow = _name_"_shadow.png";
#define EMEMY_PLANE_NORMAL(_name_) else if (name == _name_) { ENEMY_PLANE_NS(_name_) }
#define ENEMY_PLANE_BOSS(_name_) else if (name == _name_) { ENEMY_PLANE_NS(_name_) descriptor.frameNameHit = _name_"_hurt.png"; }

        EMEMY_PLANE_NORMAL("s1")
        EMEMY_PLANE_NORMAL("s2")
        EMEMY_PLANE_NORMAL("s3")
        EMEMY_PLANE_NORMAL("s4")
        EMEMY_PLANE_NORMAL("s5")
        EMEMY_PLANE_NORMAL("s6")
        ENEMY_PLANE_BOSS("boss1")
        ENEMY_PLANE_BOSS("boss2")
        ENEMY_PLANE_BOSS("boss3")
        else
        {
            throw std::exception("undefined resource name");
        }
    };

    // player's avatar
    PlayerPlane::createWithParentAndName(this, "player");

    auto s1 = EnemyPlane::createWithParentAndName(this, "s5");
    s1->setPosition(200, 800);

    auto s2 = EnemyPlane::createWithParentAndName(this, "boss3");
    s2->setPosition(100, 500);

    return true;
}

void RollingScene::menuBackCallback(cocos2d::Ref* pSender)
{
    auto rollingScene = MainScene::createScene();
    auto rollingSceneAnimated = TransitionCrossFade::create(0.5f, rollingScene);
    Director::getInstance()->replaceScene(rollingSceneAnimated);
}
