#ifndef __ENEMY_PLANE_H__
#define __ENEMY_PLANE_H__

#include "Plane.h"

class EnemyPlane : public Plane
{
public:

    static EnemyPlane * createWithParentAndName(cocos2d::Node * parent, const std::string &name);

    virtual bool initWithParent(cocos2d::Node * parent);
};

#endif