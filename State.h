#pragma once
class RockMan;
class State
{
public:
	virtual State* InputHandle(RockMan* rockman) = 0;
	virtual void Update(RockMan* rockman) = 0;
	virtual void Enter(RockMan* rockman) = 0;
	virtual void Exit(RockMan* rockman) = 0;
	virtual void Attack(RockMan* rockman) = 0;
};

