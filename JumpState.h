#pragma once
#include "State.h"
class JumpState :
    public State
{
public:
    bool isFall;
    float jumpPower;
    float jumpTime;
    float jumpLimitTime;
    virtual State* InputHandle(RockMan* rockman);
    virtual void Update(RockMan* rockman);
    virtual void Enter(RockMan* rockman);
    virtual void Exit(RockMan* rockman);
    virtual void Attack(RockMan* rockman);

};

