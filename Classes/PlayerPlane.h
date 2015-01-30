#ifndef __PLAYER_PLANE_H__
#define __PLAYER_PLANE_H__

#include "Plane.h"

class PlayerPlane : public Plane
{
public:
    PlayerPlane(void);
    ~PlayerPlane(void);

    static PlayerPlane * createWithParentAndName(cocos2d::Node * parent, const std::string &name);

    virtual bool initWithParent(cocos2d::Node * parent);

private:
    bool _bIsTouching;
    cocos2d::Vec2 _vFigherPositionDelta;
    cocos2d::Rect _rectVisible;

public:

    void update(float delta);
};

#endif