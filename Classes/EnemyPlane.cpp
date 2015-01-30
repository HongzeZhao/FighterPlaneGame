#include "EnemyPlane.h"

EnemyPlane * EnemyPlane::createWithParentAndName(cocos2d::Node * parent, const std::string &name)
{
    EnemyPlane * instance = Plane::createWithParentAndNameBase<EnemyPlane>(parent, name);
    instance->setState(NORMAL);
    return instance;
}

bool EnemyPlane::initWithParent(cocos2d::Node * parent)
{
    if (!parent)
        return false;

    parent->addChild(this);

    return true;
}