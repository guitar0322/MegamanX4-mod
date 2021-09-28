#include "stdafx.h"
#include "ColonelMelee.h"
#include "ColonelDash.h"
ColonelState* ColonelMelee::Update(Colonel* colonel)
{
	_stateTime += TIMEMANAGER->getElapsedTime();
	if (_stateTime >= 4.0f && _apearFlag == false) {
		colonel->Appear();
	}
	if (_stateTime >= 4.5f && _hitCheckFlag == false) {
		_hitCheckFlag = true;
		colonel->CheckHit();
	}
	if (_stateTime >= 6.0f) {
		_stateTime = 0;
		return new ColonelDash();
	}
    return nullptr;
}

void ColonelMelee::Enter(Colonel* colonel)
{
	_hitCheckFlag = false;
	_apearFlag = false;
	colonel->Disappear();
}

void ColonelMelee::Exit(Colonel* colonel)
{
}
