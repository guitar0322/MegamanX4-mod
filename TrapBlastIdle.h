#pragma once
#include "TrapBlastState.h"
class TrapBlast;
class TrapBlastIdle :
    public TrapBlastState
{
private:
    float _attackTerm;
    float _idleTime;
public:
    virtual TrapBlastState* Update(TrapBlast* trapBlast);
    virtual void Enter(TrapBlast* trapBlast);
    virtual void Exit(TrapBlast* trapBlast);
};

