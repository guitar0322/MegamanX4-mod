#pragma once
#include "TrapBlastState.h"
class TrapBlastAttack :
    public TrapBlastState
{
private:
    float _attackCastTime;
    float _timeStack;
public:
    virtual TrapBlastState* Update(TrapBlast* trapBlast);
    virtual void Enter(TrapBlast* trapBlast);
    virtual void Exit(TrapBlast* trapBlast);
};

