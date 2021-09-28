#pragma once
#include "ColonelState.h"
class ColonelMelee :
    public ColonelState
{
private:
	float _stateTime;
	bool _hitCheckFlag;
	bool _apearFlag;
public:
	virtual ColonelState* Update(Colonel* colonel);
	virtual void Enter(Colonel* colonel);
	virtual void Exit(Colonel* colonel);
};

