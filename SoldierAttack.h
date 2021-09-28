#pragma once
#include "SoldierState.h"
class SoldierAttack :
    public SoldierState
{
private:
	float _attackNum;
	float _attackMaxNum;
	float _attackTime;
	float _attackTerm;
public:
	virtual SoldierState* Update(Soldier* soldier);
	virtual void Enter(Soldier* soldier);
};

