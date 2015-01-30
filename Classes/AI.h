#ifndef __AI_H__
#define __AI_H__

class GameEntity;
class AI
{
public:
    virtual void update(GameEntity * target) = 0;
};

#endif