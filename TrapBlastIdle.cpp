#include "stdafx.h"
#include "TrapBlastIdle.h"
#include "TrapBlast.h"
#include "TrapBlastAttack.h"
TrapBlastState* TrapBlastIdle::Update(TrapBlast* trapBlast)
{
	float distance =
		GetDistance
		(
			trapBlast->transform->GetX(), trapBlast->transform->GetY(),
			trapBlast->rockman->transform->GetX(), trapBlast->transform->GetY()
		);
	_idleTime += TIMEMANAGER->getElapsedTime();
	if (distance <= 350 && _idleTime >= _attackTerm) {
		return new TrapBlastAttack();
	}
	return nullptr;
}

void TrapBlastIdle::Enter(TrapBlast* trapBlast)
{
	_idleTime = 0;
	_attackTerm = 4.0f;
	if (trapBlast->isDead == true) {
		if (trapBlast->dir == false) {
			trapBlast->ChangeClip("intro_right", false);
		}
		else {
			trapBlast->ChangeClip("intro_left", false);
		}
		trapBlast->isDead = false;
	}
	else {
		if (trapBlast->dir == false) {
			trapBlast->ChangeClip("idle_right", false);
		}
		else {
			trapBlast->ChangeClip("idle_left", false);
		}
	}
}

void TrapBlastIdle::Exit(TrapBlast* trapBlast)
{
}
