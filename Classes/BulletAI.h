#ifndef __BULLETAI_H__
#define __BULLETAI_H__

#include "cocos2d.h"
#include "AI.h"

class BulletAI : public AI
{
public:
    BulletAI(const cocos2d::Vec2 &velocity, const cocos2d::Vec2 &acceleration = cocos2d::Vec2::ZERO);
    void update(GameEntity * target);

protected:
    cocos2d::Vec2 _velocity;
    cocos2d::Vec2 _acceleration;
};

#endif