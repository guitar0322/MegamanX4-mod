#include "stdafx.h"
#include "ColonelRange.h"
#include "ColonelMelee.h"
ColonelState* ColonelRange::Update(Colonel* colonel)
{
    _stateTime += TIMEMANAGER->getElapsedTime();
    if (_stateTime >= 1.5f) {
        _stateTime = 0;
        if (_slashNum == 3) {
            return new ColonelMelee();
        }
        if (_upDownFlag == false)
            colonel->ChangeClip("upsword");
        else 
            colonel->ChangeClip("downsword");
        _upDownFlag = !_upDownFlag;
        colonel->FireProjectile();
        _slashNum++;
    }
    return nullptr;
}

void ColonelRange::Enter(Colonel* colonel)
{
    colonel->ChangeClip("downsword");
    colonel->FireProjectile();
    _slashNum = 1;
    _upDownFlag = false;
}

void ColonelRange::Exit(Colonel* colonel)
{
}
