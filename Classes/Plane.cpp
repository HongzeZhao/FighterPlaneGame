#include "Plane.h"

USING_NS_CC;

Plane::InitializeFunc Plane::onSetResourcesWithName;


void Plane::initializeResources(ResourceDescriptor &res)
{
    this->removeAllChildren();

    if (!res.frameNameNormal.empty())
    {
        _pSpriteNormal = Sprite::createWithSpriteFrameName(res.frameNameNormal);
        if (res.actionNormal)
            _pSpriteNormal->runAction(res.actionNormal);
        this->addChild(_pSpriteNormal);
    }
    if (!res.frameNameHit.empty())
    {
        _pSpriteHit = Sprite::createWithSpriteFrameName(res.frameNameHit);
        if (res.actionHit)
            _pSpriteHit->runAction(res.actionHit);
        this->addChild(_pSpriteHit);
    }
    if (!res.frameNameShadow.empty())
    {
        _pSpriteShadow = Sprite::createWithSpriteFrameName(res.frameNameShadow);
        _pSpriteShadow->setPosition(-30, -30); // shadow offset
        if (res.actionShadow)
            _pSpriteShadow->runAction(res.actionShadow);
        this->addChild(_pSpriteShadow);
    }
    if (!res.frameNameInvincible.empty())
    {
        _pSpriteInvincible = Sprite::createWithSpriteFrameName(res.frameNameInvincible);
        if (res.actionInvincible)
            _pSpriteInvincible->runAction(res.actionInvincible);
        this->addChild(_pSpriteInvincible);
    }
}

void Plane::Hit(GameEntity *pSender)
{
    if (this->getState() == DEAD || this->getState() == INVINCIBLE)
        return;

    this->_nLife -= pSender->getDamage();
    if (this->_nLife <= 0)
        this->setState(DEAD);
    else
        this->setState(HIT);

    if (onHit) onHit(this);
}

int Plane::getState()
{
    return _nState;
}

void Plane::setState(int state)
{
    if (_nState == state)
        return;

    if (state == DEAD)
    {
        this->setVisible(false);
    }
    else if (state == NORMAL)
    {
        this->setVisible(true);
        if (_pSpriteInvincible) _pSpriteShadow->setVisible(true);
        if (_pSpriteHit) _pSpriteHit->setVisible(false);
        if (_pSpriteNormal) _pSpriteNormal->setVisible(true);
        if (_pSpriteInvincible) _pSpriteInvincible->setVisible(false);
    }
    else if (state == INVINCIBLE)
    {
        setState(NORMAL);
        if (_pSpriteInvincible) _pSpriteInvincible->setVisible(true);
        if (_pSpriteNormal) _pSpriteNormal->runAction(Blink::create(3.0f, 10));
        scheduleOnce(schedule_selector(Plane::stateDelayEnded), 3.0f);
    }
    else if (state == HIT)
    {
        setState(NORMAL);
        if (_pSpriteHit) _pSpriteHit->setVisible(true);
        if (_pSpriteNormal) _pSpriteNormal->setVisible(false);
        scheduleOnce(schedule_selector(Plane::stateDelayEnded), 0.5f);
    }
    else
    {
        throw std::exception("Unknown state");
    }
    _nState = state;
}

void Plane::stateDelayEnded(float)
{
    setState(NORMAL);
}

void Plane::EmitBullet(float timeDelta)
{
    if (emitBulletInterval <= 0.0f) return;

    _fTimeEllapsedBullet += timeDelta;
    if (_fTimeEllapsedBullet >= emitBulletInterval)
    {
        _fTimeEllapsedBullet -= this->emitBulletInterval;
        if (_fTimeEllapsedBullet > this->emitBulletInterval)
            _fTimeEllapsedBullet = 0.0f;
        if (onEmitBullet) onEmitBullet(this);
    }
}

void Plane::EmitBomb(float timeDelta)
{
    if (emitBombInterval <= 0.0f) return;
    
    _fTimeEllapsedBomb += timeDelta;
    if (_fTimeEllapsedBomb >= emitBombInterval)
    {
        _fTimeEllapsedBomb -= this->emitBombInterval;
        if (_fTimeEllapsedBomb > this->emitBombInterval)
            _fTimeEllapsedBomb = 0.0f;
        if (onEmitBomb) onEmitBomb(this);
    }
}