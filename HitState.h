#pragma once
#include "State.h"
class HitState :
    public State
{
private:
    float _hitTime;
    float _fallSpeed;
    float _knockbackSpeed;
    float _friction;
    bool _isIdle;
public:
    virtual State* InputHandle(RockMan* rockman);
    virtual void Update(RockMan* rockman);
    virtual void Enter(RockMan* rockman);
    virtual void Exit(RockMan* rockman);
    virtual void Attack(RockMan* rockman);
};

