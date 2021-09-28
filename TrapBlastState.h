#pragma once
class TrapBlastState
{
public:
    virtual TrapBlastState* Update(TrapBlast* trapBlast) = 0;
    virtual void Enter(TrapBlast* trapBlast) = 0;
    virtual void Exit(TrapBlast* trapBlast) = 0;
};

