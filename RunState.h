#pragma once
#include "State.h"

class RunState :
    public State
{
    bool isFall;
    virtual State* InputHandle(RockMan* rockman);
    virtual void Update(RockMan* rockman);
    virtual void Enter(RockMan* rockman);
    virtual void Exit(RockMan* rockman);
    virtual void Attack(RockMan* rockman);
};

