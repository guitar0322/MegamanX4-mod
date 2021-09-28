#pragma once
#include "State.h"
class IntroState :
    public State
{
private:
    float _introTime;
public:
    virtual State* InputHandle(RockMan* rockman);
    virtual void Update(RockMan* rockman);
    virtual void Enter(RockMan* rockman);
    virtual void Exit(RockMan* rockman);
    virtual void Attack(RockMan* rockman);
};

