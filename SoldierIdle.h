#pragma once
#include "SoldierState.h"
class SoldierIdle :
    public SoldierState
{
private:
	float _attackTerm;
	float _idleTime;
public:
	virtual SoldierState* Update(Soldier* soldier);
	virtual void Enter(Soldier* soldier);
};

