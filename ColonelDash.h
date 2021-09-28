#pragma once
#include "ColonelState.h"
class ColonelDash :
    public ColonelState
{
private:
	float _dashSpeed;
	float _friction;
public:
	virtual ColonelState* Update(Colonel* colonel);
	virtual void Enter(Colonel* colonel);
	virtual void Exit(Colonel* colonel);
};

