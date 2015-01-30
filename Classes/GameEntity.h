#ifndef __GAME_ENTITY_H__
#define __GAME_ENTITY_H__

#include "cocos2d.h"

class AI;
class GameEntity : public cocos2d::Node
{
public:
    enum EntityType
    {
        PLAYER,
        ENEMY,
        BONUS,
        BULLET,
        NONE
    };

    CC_SYNTHESIZE(int, _nType, Type);
    CC_SYNTHESIZE(int, _nDamage, Damage);       // damage it course due to explosion
    CC_SYNTHESIZE_READONLY(float, _nAge, Age);  // how long it lives since created

    GameEntity() : cocos2d::Node(), _nType(NONE), _nDamage(0), _nAge(0.0f) {}

    virtual void update(float delta)
    {
        cocos2d::Node::update(delta);
        _nAge += delta;
    }

    virtual void runAI(AI * /* pAI */) {}
};

#endif