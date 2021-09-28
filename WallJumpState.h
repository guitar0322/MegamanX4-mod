#pragma once
#include "State.h"
class WallJumpState :
    public State
{
    float wallJumpPowerY;
    float wallJumpTime;
    float wallJumpPowerX;
    float airResistance;

    virtual State* InputHandle(RockMan* rockman);
    virtual void Update(RockMan* rockman);
    virtual void Enter(RockMan* rockman);
    virtual void Exit(RockMan* rockman);
    virtual void Attack(RockMan* rockman);
};

