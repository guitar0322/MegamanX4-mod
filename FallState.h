#pragma once
#include "State.h"
class FallState :
    public State
{
public:
    float speedY;
    bool isGround;
    virtual State* InputHandle(RockMan* rockman);
    virtual void Update(RockMan* rockman);
    virtual void Enter(RockMan* rockman);
    virtual void Exit(RockMan* rockman);
    virtual void Attack(RockMan* rockman);

};

