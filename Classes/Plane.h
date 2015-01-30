#ifndef __PLANE_H__
#define __PLANE_H__

#include "GameEntity.h"

class Plane : public GameEntity
{
public:
    enum PlaneState
    {
        DEAD,
        INVINCIBLE,
        NORMAL,
        HIT
    };

public:
    struct ResourceDescriptor
    {
        std::string frameNameNormal;
        std::string frameNameShadow;
        std::string frameNameHit;
        std::string frameNameInvincible;

        cocos2d::Action * actionNormal;
        cocos2d::Action * actionShadow;
        cocos2d::Action * actionHit;
        cocos2d::Action * actionInvincible;

        ResourceDescriptor(): actionNormal(NULL), actionShadow(NULL), actionHit(NULL), actionInvincible(NULL) {}
    };

    typedef std::function<void(Plane::ResourceDescriptor &resource, const std::string &name)> InitializeFunc;
    static InitializeFunc onSetResourcesWithName;

    CC_PROPERTY(int, _nState, State);
    CC_SYNTHESIZE(int, _nLife, Life);
    CC_SYNTHESIZE_READONLY(int, _nLifeLimit, LifeLimit);

    Plane(): GameEntity(), 
        _fTimeEllapsedBullet(0.0f), _fTimeEllapsedBomb(0.0f),
        emitBulletInterval(0.2f), emitBombInterval(1.0f),
        _pSpriteShadow(NULL), _pSpriteHit(NULL), _pSpriteNormal(NULL), _pSpriteInvincible(NULL)
    { }

    template <typename DerivativePlaneType>
    static DerivativePlaneType * createWithParentAndNameBase(cocos2d::Node * parent, const std::string &name)
    {
        DerivativePlaneType * instance = new DerivativePlaneType();
        if (instance && instance->initWithParent(parent))
        {
            instance->autorelease();

            if (!onSetResourcesWithName)
                throw std::exception("Initialize function empty");

            ResourceDescriptor resDescriptor;
            onSetResourcesWithName(resDescriptor, name);
            instance->initializeResources(resDescriptor);
        }
        else
            CC_SAFE_DELETE(instance);
        return instance;
    }

    virtual bool initWithParent(cocos2d::Node * parent) = 0;

protected:

    virtual void initializeResources(ResourceDescriptor &);

public:
    typedef std::function<void(Plane *pPlane)> EventHandlerFunc;

    EventHandlerFunc onDead;
    EventHandlerFunc onEmitBullet;
    EventHandlerFunc onEmitBomb;
    EventHandlerFunc onHit;

    float emitBulletInterval;
    float emitBombInterval;

    virtual void Hit(GameEntity *pSender);
    virtual void EmitBullet(float timeDelta);
    virtual void EmitBomb(float timeDelta);

protected:

    cocos2d::Sprite * _pSpriteNormal;
    cocos2d::Sprite * _pSpriteShadow;
    cocos2d::Sprite * _pSpriteHit;
    cocos2d::Sprite * _pSpriteInvincible;

private:
    float _fTimeEllapsedBullet;
    float _fTimeEllapsedBomb;

    void stateDelayEnded(float);
};

#endif