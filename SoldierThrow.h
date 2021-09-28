#pragma once
#include "SoldierState.h"
class SoldierThrow :
    public SoldierState
{
private:
	float _throwTime;
	float _throwLimit;
	float _throwCastTime;
public:
	virtual SoldierState* Update(Soldier* soldier);
	virtual void Enter(Soldier* soldier);
};

