#pragma once
#include "ColonelState.h"
class ColonelIdle :
    public ColonelState
{
private:
	int _nextState;
	float _stateTime;
public:
	virtual ColonelState* Update(Colonel* colonel);
	virtual void Enter(Colonel* colonel);
	virtual void Exit(Colonel* colonel);
};

