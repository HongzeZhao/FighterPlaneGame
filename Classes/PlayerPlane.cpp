#include "PlayerPlane.h"

USING_NS_CC;

PlayerPlane * PlayerPlane::createWithParentAndName(cocos2d::Node * parent, const std::string &name)
{
    PlayerPlane * instance = Plane::createWithParentAndNameBase<PlayerPlane>(parent, name);
    instance->setState(INVINCIBLE);
    return instance;
}

PlayerPlane::PlayerPlane()
{
    this->setType(PLAYER);
}

bool PlayerPlane::initWithParent(cocos2d::Node * parent)
{
    if (!parent)
        return false;

    bool ret = this->init();

    auto director = Director::getInstance();
    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    _rectVisible = Rect(origin.x, origin.y, visibleSize.width, visibleSize.height);

    parent->addChild(this);
    this->runAction(MoveTo::create(1.0f, Vec2(visibleSize.width/2, visibleSize.height/4)));

    // register touches event
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = [&](const std::vector<Touch*>& touches, Event *unused_event)
    {
        _bIsTouching = true;
        _vFigherPositionDelta = Vec2::ZERO;
    };
    listener->onTouchesMoved = [&](const std::vector<Touch*>& touches, Event *unused_event)
    {
        if (_bIsTouching && !touches.empty())
            _vFigherPositionDelta += touches.front()->getDelta();
    };
    listener->onTouchesEnded = [&](const std::vector<Touch*>& touches, Event *unused_event)
    {
        _bIsTouching = false;
    };
    listener->onTouchesCancelled = [&](const std::vector<Touch*>& touches, Event *unused_event)
    {
        _bIsTouching = false;
    };
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, parent);

    scheduleUpdate();

    return ret;
}


PlayerPlane::~PlayerPlane(void)
{
}

void PlayerPlane::update(float delta)
{
    Plane::update(delta);
    
    if (_bIsTouching)
    {
        Vec2 pos = this->getPosition() + _vFigherPositionDelta;
        if (_rectVisible.containsPoint(pos))
            this->setPosition(pos);
        _vFigherPositionDelta = Vec2::ZERO;
    }
}