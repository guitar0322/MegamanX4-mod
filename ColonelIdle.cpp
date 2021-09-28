#include "stdafx.h"
#include "ColonelIdle.h"
#include "ColonelRange.h"
ColonelState* ColonelIdle::Update(Colonel* colonel)
{
	_stateTime += TIMEMANAGER->getElapsedTime();
	if (_stateTime >= 3.0f) {
		if (_nextState == 0) {
			return new ColonelRange();
		}
		else if (_nextState == 1) {

		}
	}
    return nullptr;
}

void ColonelIdle::Enter(Colonel* colonel)
{
	_stateTime = 0;
	_nextState = RND->getInt(1);
	colonel->ChangeClip("idle");
}

void ColonelIdle::Exit(Colonel* colonel)
{
}
