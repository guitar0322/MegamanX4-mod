#pragma once
#include "State.h"
class GroundState :
    public State
{
public:
    float groundTime;
    virtual State* InputHandle(RockMan* rockman);
    virtual void Update(RockMan* rockman);
    virtual void Enter(RockMan* rockman);
    virtual void Exit(RockMan* rockman);
    virtual void Attack(RockMan* rockman);

};

