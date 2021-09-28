#include "stdafx.h"
#include "ColonelDash.h"
#include "ColonelIdle.h"
ColonelState* ColonelDash::Update(Colonel* colonel)
{
	if (colonel->_dir == false) {
		if (colonel->transform->GetX() <= 9900 + WINSIZEX / 2 - 80) {
			colonel->transform->MoveX(_dashSpeed * TIMEMANAGER->getElapsedTime());
		}
		else {
			colonel->_dir = true;
			return new ColonelIdle();
		}
	}
	else {
		if (colonel->transform->GetX() >= 9900 - WINSIZEX / 2 + 80) {
			colonel->transform->MoveX(-_dashSpeed * TIMEMANAGER->getElapsedTime());
		}
		else {
			colonel->_dir = false;
			return new ColonelIdle();
		}
	}
	_dashSpeed -= _friction * TIMEMANAGER->getElapsedTime();
	if (_dashSpeed < 100)
		_dashSpeed = 100;
    return nullptr;
}

void ColonelDash::Enter(Colonel* colonel)
{
    colonel->SetDashDir();
	colonel->ChangeClip("dash");
    _dashSpeed = 250;
    _friction = 80;
}

void ColonelDash::Exit(Colonel* colonel)
{
}
