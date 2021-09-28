#pragma once
#include "State.h"
class WallState :
    public State
{
public:
    RECT sideRc;
    float slipSpeed;
    bool isGround;
    bool isFall;
    virtual State* InputHandle(RockMan* rockman);
    virtual void Update(RockMan* rockman);
    virtual void Enter(RockMan* rockman);
    virtual void Exit(RockMan* rockman);
    virtual void Attack(RockMan* rockman);
    bool CheckWall(RockMan* rockman);
};

