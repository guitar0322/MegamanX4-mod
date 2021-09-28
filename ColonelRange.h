#pragma once
#include "ColonelState.h"
class ColonelRange :
    public ColonelState
{
private:
	float _stateTime;
	int _slashNum;
	bool _upDownFlag;
public:
	virtual ColonelState* Update(Colonel* colonel);
	virtual void Enter(Colonel* colonel);
	virtual void Exit(Colonel* colonel);
};

