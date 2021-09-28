#pragma once
class Soldier;
class SoldierState
{
public:
	virtual SoldierState* Update(Soldier* soldier) = 0;
	virtual void Enter(Soldier* soldier) = 0;
};

