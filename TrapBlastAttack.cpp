#include "stdafx.h"
#include "TrapBlastAttack.h"
#include "TrapBlastIdle.h"

TrapBlastState* TrapBlastAttack::Update(TrapBlast* trapBlast)
{
    _timeStack += TIMEMANAGER->getElapsedTime();
    if (_timeStack >= _attackCastTime) {
        ProjectileManager::GetInstance()->FireTrapBlastProjectile(
            trapBlast->transform->GetX() + (trapBlast->dir ? -45 : 45), 
            trapBlast->transform->GetY(), false);
        return new TrapBlastIdle();
    }
    return nullptr;
}

void TrapBlastAttack::Enter(TrapBlast* trapBlast)
{
    _attackCastTime = 2.0f;
    _timeStack = 0;
    if (trapBlast->dir == false) {
        trapBlast->ChangeClip("attack_right", false);
    }
    else {
        trapBlast->ChangeClip("attack_left", false);
    }
}

void TrapBlastAttack::Exit(TrapBlast* trapBlast)
{
}
